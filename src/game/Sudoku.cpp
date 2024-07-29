//
// Created by nyanbanan on 23.03.24.
//

#include "Sudoku.hpp"

namespace Game {
    Sudoku::Sudoku(QObject *parent) : QObject(parent), _gridStyle(9) {
        connect(this, &Sudoku::gridChanged, this, &Sudoku::onGridChanged);

//        _recordStorage.parse(STORAGE_PATH);
    }

    Sudoku::~Sudoku() {
//        _recordStorage.save(STORAGE_PATH);
    }

    void Sudoku::start(unsigned int difficulty) {
        unsigned int count = 0;

        if (difficulty == 0) {
            difficulty = 1;
        } else {
            if (!_erasingDifficulty.contains(difficulty)) {
                difficulty = 3;
            }
        }

        count = _erasingDifficulty[difficulty];

        _answerGrid = std::make_unique<SudokuGrid>(_grid);

        _grid.cleanRandomCells(count);

        for (int i = 0; i < _grid.rowCount(); ++i) {
            for (int j = 0; j < _grid.columnCount(); ++j) {
                if (_grid.data(i, j).toInt() == 0) {
                    _emptyCells.emplace(i, j);
                    _gridStyle.setCellBackgroundColor(i, j, QColor::fromString("#413a3a"));
                }
            }
        }
    }

    void Sudoku::playerMove(int row, int column, unsigned int value) {
        if (checkHint()) {
            afterHint();
        }

        if (_emptyCells.contains(std::make_pair(row, column))) {
            _grid.setCellValue(row, column, value);

            emit gridChanged();
        }
    }

    void Sudoku::playerHint() {
        if (checkHint()) {
            afterHint();
        }

        std::pair<int, int> hintCellIndex;
        QColor hintColor;
        for (auto index: _emptyCells) {
            auto cell = _grid.data(index.first, index.second).toInt();
            if (cell != 0) {
                if (cell != _answerGrid->data(index.first, index.second).toInt()) {
                    hintColor = QColor(Qt::red);
                    hintCellIndex = index;
                    break;
                }
            } else {
                hintColor = QColor(Qt::blue);
                hintCellIndex = index;
            }
        }
        _lastTipCell.index = hintCellIndex;
        _lastTipCell.color = _gridStyle.getCellBorderColor(hintCellIndex.first, hintCellIndex.second);

        _gridStyle.setCellBorderColor(hintCellIndex.first, hintCellIndex.second, hintColor);

        _grid.setCellValue(hintCellIndex.first, hintCellIndex.second,
                           _answerGrid->data(hintCellIndex.first, hintCellIndex.second).toInt());

        _emptyCells.erase(hintCellIndex);

        emit gridChanged();
    }

    void Sudoku::onGridChanged() {
        if (!_grid.containsEmptyCells()) {
            if (_grid.validate()) {
                emit win();
            }
        }
    }

    bool Sudoku::checkHint() const {
        return _lastTipCell.index.first != -1 || _lastTipCell.index.second != -1;
    }

    void Sudoku::afterHint() {
        _gridStyle.setCellBorderColor(_lastTipCell.index.first, _lastTipCell.index.second,
                                      _lastTipCell.color);
        _gridStyle.setCellBackgroundColor(_lastTipCell.index.first, _lastTipCell.index.second,
                                      QColor::fromString(SudokuGridStyle::defaultBackground));
        _grid.callDataChanged(_lastTipCell.index.first, _lastTipCell.index.second);

        _lastTipCell.index = {-1,-1};
    }

    Game::SudokuGrid *Sudoku::getGrid() {
        return &_grid;
    }

    Game::SudokuGridStyle *Sudoku::getGridStyle() {
        return &_gridStyle;
    }

    QString Sudoku::getDifficultyName(int difficulty) {
        auto name = "";

        switch (difficulty) {
            case 1: {
                name = Records::Constants::EASY.c_str();
                break;
            }
            case 2 : {
                name = Records::Constants::MEDIUM.c_str();
                break;
            }
            case 3 : {
                name = Records::Constants::HARD.c_str();
                break;
            }
            case 4 : {
                name = Records::Constants::EXTREME.c_str();
                break;
            }
            default:
                name = "undefined";
        }

        return {name};
    }

//    Records::JsonStorage *Sudoku::getStorage() {
//        return &_recordStorage;
//    }
}
