//
// Created by nyanbanan on 24.03.24.
//

#ifndef SUDOKU_SUDOKUGRIDSTYLE_HPP
#define SUDOKU_SUDOKUGRIDSTYLE_HPP

#include <QObject>
#include <QtQml>
#include <QColor>

#include "SudokuGrid.hpp"

namespace Game {
    class SudokuGridStyle : public QObject {
        Q_OBJECT
        QML_ELEMENT
    public:
        explicit SudokuGridStyle(unsigned int N = 9, QObject* parent = nullptr);

        Q_INVOKABLE QColor getCellBorderColor(int row, int column);
        Q_INVOKABLE QColor getCellBackgroundColor(int row, int column);
        Q_INVOKABLE QColor getCellTextColor(int row, int column);

        void setCellBorderColor(int row, int column, QColor color);
        void setCellBackgroundColor(int row, int column, QColor color);
        void setCellTextColor(int row, int column, QColor color);

        static inline QString defaultBackground = "#5d5454";
    private:
        struct Style {
            QColor border;
            QColor background;
            QColor text;
        };

        void init(unsigned int N);

        std::map<std::pair<unsigned int, unsigned int>, Style> _styles;
    };
} // Game

#endif //SUDOKU_SUDOKUGRIDSTYLE_HPP
