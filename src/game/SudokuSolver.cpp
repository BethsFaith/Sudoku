//
// Created by nyanbanan on 23.03.24.
//

#include "SudokuSolver.hpp"

namespace Game {
    int SudokuSolver::solve(unsigned int (*grid)[N]) {
        std::set<unsigned int> possibleValues;
        unsigned int* cell = nullptr;
        int solutions = 0;

        for (int i{}; i < N; ++i) {
            for (int j{}; j < N; ++j) {
                if (grid[i][j] == 0) {
                    cell = &grid[i][j];

                    possibleValues = findPossibleValues({.row = i, .column = j}, grid);

                    break;
                }
            }
            if (cell != nullptr) {
                break;
            }
        }

        if (cell != nullptr) {
            if (possibleValues.empty()) {
                return 0;
            }

            for (const auto& value : possibleValues) {
                *cell = value;

                solutions += solve(grid);
            }
        } else {
            return 1;
        }

        return solutions;
    }

    std::set<unsigned int> SudokuSolver::findPossibleValues(SudokuSolver::Index cellIndex, unsigned int grid[N][N]) {
        std::set<unsigned int> existValues;

        existValues.merge(getRowValues(cellIndex.row, grid));
        existValues.merge(getColumnValues(cellIndex.column, grid));
        existValues.merge(getBlockValue(cellIndex, grid));

        std::set<unsigned int> possibleValues = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (const auto& value : existValues) {
            if (possibleValues.contains(value)) {
                possibleValues.erase(value);
            }
        }

        return possibleValues;
    }

    std::set<unsigned int> SudokuSolver::getRowValues(int row, unsigned int (*grid)[N]) {
        std::set<unsigned int> values;

        for (int j{}; j < N; ++j) {
            values.insert(grid[row][j]);
        }

        return values;
    }

    std::set<unsigned int> SudokuSolver::getColumnValues(int column, unsigned int (*grid)[N]) {
        std::set<unsigned int> values;

        for (int i{}; i < N; ++i) {
            values.insert(grid[i][column]);
        }

        return values;
    }

    std::set<unsigned int> SudokuSolver::getBlockValue(SudokuSolver::Index index, unsigned int (*grid)[N]) {
        std::set<unsigned int> values;

        int blockRowStart = 3 * (index.row / 3);
        int blockColumnStart = 3 * (index.column / 3);
        for (int i{}; i < 3; ++i) {
            for (int j{}; j < 3; ++j) {
                values.insert(grid[blockRowStart + i][blockColumnStart + j]);
            }
        }

        return values;
    }

    bool SudokuSolver::validate(unsigned int (*grid)[N]) {
        for (int i{}; i < N; ++i) {
            if (!validateRow(i, grid) || !validateColumn(i, grid)) {
                return false;
            }
        }

        return true;
    }

    bool SudokuSolver::validateRow(int row, unsigned int (*grid)[N]) {
        std::map<unsigned int, unsigned int> values;

        for (int j{}; j < N; ++j) {
            ++values[(grid[row][j])];
        }
        auto res = !std::ranges::any_of(values, [](auto pair){
            return pair.second > 1;
        });

        return res;
    }

    bool SudokuSolver::validateColumn(int column, unsigned int (*grid)[N]) {
        std::map<unsigned int, unsigned int> values;

        for (int j{}; j < N; ++j) {
            ++values[(grid[j][column])];
        }
        auto res = !std::ranges::any_of(values, [](auto pair){
            return pair.second > 1;
        });

        return res;
    }

    bool SudokuSolver::validateBlock(SudokuSolver::Index index, unsigned int (*grid)[N]) {
        std::map<unsigned int, unsigned int> values;

        int blockRowStart = 3 * (index.row / 3);
        int blockColumnStart = 3 * (index.column / 3);
        for (int i{}; i < 3; ++i) {
            for (int j{}; j < 3; ++j) {
                ++values[(grid[blockRowStart + i][blockColumnStart + j])];
            }
        }

        auto res = std::ranges::any_of(values, [](auto pair){
            return pair.second > 1;
        });

        return res;
    }
} // Game