//
// Created by nyanbanan on 23.03.24.
//

#ifndef SUDOKU_SUDOKUSOLVER_HPP
#define SUDOKU_SUDOKUSOLVER_HPP

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

namespace Game {
    class SudokuSolver {
    public:
        static inline const int N = 9;

        static int solve(unsigned int grid[N][N]);

        static bool validate(unsigned int grid[N][N]);
    private:
        struct Index {
            int row;
            int column;
        };

        static std::set<unsigned int> findPossibleValues(Index cellIndex, unsigned int grid[N][N]);
        static std::set<unsigned int> getRowValues(int row, unsigned int grid[N][N]);
        static std::set<unsigned int> getColumnValues(int column, unsigned int grid[N][N]);
        static std::set<unsigned int> getBlockValue(Index index, unsigned int grid[N][N]);

        static bool validateRow(int row, unsigned int grid[N][N]);
        static bool validateColumn(int column, unsigned int grid[N][N]);
        static bool validateBlock(Index index, unsigned int grid[N][N]);
    };

} // Game

#endif //SUDOKU_SUDOKUSOLVER_HPP
