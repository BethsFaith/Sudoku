//
// Created by nyanbanan on 21.03.24.
//

#ifndef MOBILEGAME2_GRID_HPP
#define MOBILEGAME2_GRID_HPP

#include <iostream>

#include <QObject>
#include <QtQml>
#include <QRandomGenerator>
#include <QColor>

#include "SudokuSolver.hpp"

namespace Game {
    class SudokuGrid : public QAbstractTableModel {
    Q_OBJECT
    QML_ELEMENT
    public:
        explicit SudokuGrid(QObject *parent = nullptr);
        SudokuGrid(const SudokuGrid& other);

        void cleanRandomCells(unsigned int count);

        bool containsEmptyCells();
        bool validate();

        void callDataChanged(int row, int column);

        void setCellValue(int row, int column, unsigned int value);

        Q_INVOKABLE [[nodiscard]] QVariant data(int row, int column) const;
        Q_INVOKABLE [[nodiscard]] QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

        [[nodiscard]] int rowCount(const QModelIndex & = QModelIndex()) const override;
        [[nodiscard]] int columnCount(const QModelIndex & = QModelIndex()) const override;

        [[nodiscard]] static unsigned int getBlock(int row, int column);
    private:
        void init();

        void shuffle();
        void transpose();
        void swapRandomRows();
        void swapRandomColumns();
        void swapRandomBlockRows();
        void swapRandomBlockColumns();
        void print();

        static inline const int N = 9;
        unsigned int _grid[N][N]{};
    };
} // Game

#endif //MOBILEGAME2_GRID_HPP
