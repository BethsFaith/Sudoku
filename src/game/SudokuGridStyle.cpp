//
// Created by nyanbanan on 24.03.24.
//

#include "SudokuGridStyle.hpp"

namespace Game {
    SudokuGridStyle::SudokuGridStyle(unsigned int N, QObject* parent) : QObject(parent) {
        init(N);
    }

    void SudokuGridStyle::init(unsigned int N) {
        for (int i = 0; i < N; ++ i) {
            for (int j = 0; j < N; ++j) {
                auto row = i/3;
                auto column = j/3;

                QColor border, background, text;

                auto area = SudokuGrid::getBlock(row, column);
                switch (area%9) {
                    case 1 : {
                        border = (Qt::green);
                        background = QColor::fromString(defaultBackground);
                        text = (Qt::white);
                        break;
                    }
                    case 2 :{
                        border = QColor(Qt::yellow);
                        background = QColor::fromString(defaultBackground);
                        text = (Qt::white);
                        break;
                    }
                    case 3 : {
                        border = QColor(Qt::cyan);
                        background = QColor::fromString(defaultBackground);
                        text = (Qt::white);
                        break;
                    }
                    case 4 : {
                        border = QColor(Qt::magenta);
                        background = QColor::fromString(defaultBackground);
                        text = (Qt::white);
                        break;
                    }
                    case 5 : {
                        border = QColor(Qt::white);
                        background = QColor::fromString(defaultBackground);
                        text = (Qt::white);
                        break;
                    }
                    case 6 : {
                        border = QColor(Qt::magenta);
                        background = QColor::fromString(defaultBackground);
                        text = (Qt::white);
                        break;
                    }
                    case 7 : {
                        border = QColor(Qt::cyan);
                        background = QColor::fromString(defaultBackground);
                        text = (Qt::white);
                        break;
                    }
                    case 8 : {
                        border = QColor(Qt::yellow);
                        background = QColor::fromString(defaultBackground);
                        text = (Qt::white);
                        break;
                    }
                    case 0 :
                    default: {
                        border = QColor(Qt::green);
                        background = QColor::fromString(defaultBackground);
                        text = (Qt::white);
                        break;
                    }
                }
                _styles[std::make_pair(i, j)] = {.border = border, .background = background, .text = text};
            }
        }
    }

    QColor SudokuGridStyle::getCellBorderColor(int row, int column) {
        return _styles[std::make_pair(row,column)].border;
    }

    QColor SudokuGridStyle::getCellTextColor(int row, int column) {
        return _styles[std::make_pair(row,column)].text;
    }

    QColor SudokuGridStyle::getCellBackgroundColor(int row, int column) {
        return _styles[std::make_pair(row,column)].background;
    }

    void SudokuGridStyle::setCellBorderColor(int row, int column, QColor color) {
        _styles[std::make_pair(row,column)].border = color;
    }

    void SudokuGridStyle::setCellBackgroundColor(int row, int column, QColor color) {
        _styles[std::make_pair(row,column)].background = color;
    }

    void SudokuGridStyle::setCellTextColor(int row, int column, QColor color) {
        _styles[std::make_pair(row,column)].text = color;
    }
} // Game