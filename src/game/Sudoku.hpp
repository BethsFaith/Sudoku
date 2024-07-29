//
// Created by nyanbanan on 23.03.24.
//

#ifndef SUDOKU_SUDOKU_HPP
#define SUDOKU_SUDOKU_HPP

#include <QObject>
#include <QtQml>

#include "SudokuGrid.hpp"
#include "SudokuGridStyle.hpp"
#include "../records/constants.hpp"

namespace Game {
    class Sudoku : public QObject {
    Q_OBJECT
    QML_ELEMENT
    public:
        explicit Sudoku(QObject* parent = nullptr);
        ~Sudoku() override;

        Q_INVOKABLE void start(unsigned int difficulty = 1);
        Q_INVOKABLE void playerMove(int row, int column, unsigned int value);
        Q_INVOKABLE void playerHint();

        Q_INVOKABLE QString getDifficultyName(int difficulty);

        Q_PROPERTY(Game::SudokuGrid* grid READ getGrid NOTIFY gridChanged);
        Q_PROPERTY(Game::SudokuGridStyle* style READ getGridStyle NOTIFY styleChanged);

        Game::SudokuGrid* getGrid();
        Game::SudokuGridStyle* getGridStyle();

    signals:
        void gridChanged();
        void styleChanged();
        void win();

    protected:
        bool checkHint() const;
        void afterHint();

    private slots:
        void onGridChanged();
    private:
        struct Buffer {
            QColor color;
            std::pair<int, int> index{-1,-1};
        };
        const std::string STORAGE_PATH = "../src/game/records/records.json";
        std::map<unsigned int, unsigned int> _erasingDifficulty = {
                {1, 10},
                {2, 15},
                {3, 30},
                {4, 40}
        };

        SudokuGrid _grid{};
        SudokuGridStyle _gridStyle{};

        std::unique_ptr<SudokuGrid> _answerGrid{nullptr};
        std::set<std::pair<int, int>> _emptyCells;

        Buffer _lastTipCell;
//        Records::JsonStorage _recordStorage;
    };
}


#endif //SUDOKU_SUDOKU_HPP
