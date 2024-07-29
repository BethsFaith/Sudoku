//
// Created by nyanbanan on 21.03.24.
//

#include "SudokuGrid.hpp"

namespace Game {
    SudokuGrid::SudokuGrid(const SudokuGrid &other) {
        for (int i{}; i < N; ++i) {
            for (int j{}; j < N; ++j) {
                _grid[i][j] = other._grid[i][j];
            }
        }
    }

    SudokuGrid::SudokuGrid(QObject *parent) : QAbstractTableModel(parent) {
        init();

        shuffle();
    }

    void SudokuGrid::init() {
        for (int i{}; i < N; ++i) {
            for (int j{}; j < N; ++j) {
                _grid[i][j] = ((i * 3 + i/3) + j) % N + 1;
            }
        }
    }

    void SudokuGrid::shuffle() {
        auto randomCount = QRandomGenerator::global()->bounded(150,300);

        for (int i = 0; i < randomCount; ++i) {
            auto randomFunc = QRandomGenerator::global()->bounded(0,5);
            switch (randomFunc) {
                case 0:
                    transpose();
                    break;
                case 1:
                    swapRandomRows();
                    break;
                case 2:
                    swapRandomColumns();
                    break;
                case 3:
                    swapRandomBlockRows();
                    break;
                case 4:
                    swapRandomBlockColumns();
                    break;
                default:
                    break;
            }
        }
    }

    void SudokuGrid::transpose() {
        for (int i{}; i < N - 1; ++i) {
            for (int j{i + 1}; j < N; ++j) {
                auto t =  _grid[i][j];
                _grid[i][j] = _grid[j][i];
                _grid[j][i] = t;
            }
        }
    }

    void SudokuGrid::swapRandomRows() {
        uint8_t randomBlock = QRandomGenerator::global()->bounded(0, N/3) * 3;
        uint8_t randomBlockRow1 = QRandomGenerator::global()->bounded(0, 3);

        auto row1 = randomBlock + randomBlockRow1;

        auto randomBlockRow2 = QRandomGenerator::global()->bounded(0, 3);
        while (randomBlockRow2 == randomBlockRow1) {
            randomBlockRow2 = QRandomGenerator::global()->bounded(0, 3);
        }

        auto row2 = randomBlock + randomBlockRow2;

        uint8_t t;
        for (int i{}; i < N; ++i) {
            t = _grid[row1][i];
            _grid[row1][i] = _grid[row2][i];
            _grid[row2][i] = t;
        }
    }

    void SudokuGrid::swapRandomColumns() {
        uint8_t randomBlock = QRandomGenerator::global()->bounded(0, N/3) * 3;
        uint8_t randomBlockColumn1 = QRandomGenerator::global()->bounded(0, 3);

        auto column1 = randomBlock + randomBlockColumn1;

        auto randomBlockColumn2 = QRandomGenerator::global()->bounded(0, 3);
        while (randomBlockColumn2 == randomBlockColumn1) {
            randomBlockColumn2 = QRandomGenerator::global()->bounded(0, 3);
        }

        auto column2 = randomBlock + randomBlockColumn2;

        uint8_t t;
        for (int i{}; i < N; ++i) {
            t = _grid[i][column1];
            _grid[i][column1] = _grid[i][column2];
            _grid[i][column2] = t;
        }
    }

    void SudokuGrid::swapRandomBlockRows() {
        uint8_t randomBlock1 = QRandomGenerator::global()->bounded(0, N/3) * 3;
        uint8_t randomBlock2 = randomBlock1;
        while (randomBlock2 == randomBlock1) {
            randomBlock2 = QRandomGenerator::global()->bounded(0, N/3) * 3;
        }

        uint8_t t;
        for (int i{}; i < 3; ++i) {
            auto row1 = randomBlock1 + i;
            auto row2 = randomBlock2 + i;

            for (int j{}; j < N; ++j) {
                t = _grid[row1][j];
                _grid[row1][j] = _grid[row2][j];
                _grid[row2][j] = t;
            }
        }
    }

    void SudokuGrid::swapRandomBlockColumns() {
        uint8_t randomBlock1 = QRandomGenerator::global()->bounded(0, N/3) * 3;
        uint8_t randomBlock2 = randomBlock1;
        while (randomBlock2 == randomBlock1) {
            randomBlock2 = QRandomGenerator::global()->bounded(0, N/3) * 3;
        }

        uint8_t t;
        for (int i{}; i < 3; ++i) {
            auto column1 = randomBlock1 + i;
            auto column2 = randomBlock2 + i;

            for (int j{}; j < N; ++j) {
                t = _grid[j][column1];
                _grid[j][column1] = _grid[j][column2];
                _grid[j][column2] = t;
            }
        }
    }

    void SudokuGrid::cleanRandomCells(unsigned int count) {
        std::set<unsigned int*> viewedCells;

        unsigned int erasedCellCount = 0;
        int i, j;
        while (erasedCellCount != count) {
            i = QRandomGenerator::global()->bounded(0, N - 1);
            j = QRandomGenerator::global()->bounded(0, N - 1);

            if (viewedCells.contains(&_grid[i][j])) {
                continue;
            } else {
                unsigned int temp[N][N];
                for (int r = 0; r < N; ++r) {
                    for (int c = 0; c < N; ++ c) {
                        temp[r][c] = _grid[r][c];
                    }
                }
                temp[i][j] = 0;

                auto solutions = SudokuSolver::solve(temp);
                if (solutions == 1) {
                    setCellValue(i, j, 0);

                    ++erasedCellCount;
                }

                viewedCells.insert(&_grid[i][j]);
            }
        }
    }

    bool SudokuGrid::containsEmptyCells() {
        for (int i{}; i < N; ++i) {
            for (int j{}; j < N; ++j) {
                if (_grid[i][j] == 0) {
                    return true;
                }
            }
        }
        return false;
    }

    bool SudokuGrid::validate() {
        return SudokuSolver::validate(_grid);
    }

    void SudokuGrid::print() {
        std::cout << std::endl;

        for (int i{}; i < N; ++i) {
            for (int j{}; j < N; ++j) {
                std::cout << _grid[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void SudokuGrid::setCellValue(int row, int column, unsigned int value) {
        _grid[row][column] = value;

        emit dataChanged(index(row, column), index(row, column));
    }

    QVariant SudokuGrid::data(const QModelIndex &index, int role) const {
        if (role == Qt::DisplayRole) {
            if (_grid[index.row()][index.column()] == 0) {
                return "";
            } else {
                return _grid[index.row()][index.column()];
            }
        }
        return {};
    }

    QVariant SudokuGrid::data(const int row, const int column) const {
        return _grid[row][column];
    }

    int SudokuGrid::rowCount(const QModelIndex &) const {
        return N;
    }

    int SudokuGrid::columnCount(const QModelIndex &) const {
        return N;
    }

    unsigned int SudokuGrid::getBlock(int row, int column) {
        if (row == 0) {
            if (column == 0) {
                return 1;
            } else if (column == 1) {
                return 2;
            } else {
                return 3;
            }
        } else if (row == 1) {
            if (column == 0) {
                return 4;
            } else if (column == 1) {
                return 5;
            } else {
                return 6;
            }
        } else {
            if (column == 0) {
                return 7;
            } else if (column == 1) {
                return 8;
            } else {
                return 9;
            }
        }
    }

    void SudokuGrid::callDataChanged(int row, int column) {
        emit dataChanged(index(row, column), index(row, column));
    }
} // Game