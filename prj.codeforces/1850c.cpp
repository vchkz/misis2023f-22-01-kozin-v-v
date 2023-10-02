#include <iostream>
#include <vector>
#include <string>

const int ROWS = 8;
const int COLS = 8;

int main() {
    int test_cases;
    std::cin >> test_cases;

    while (test_cases--) {
        std::vector <std::string> grid(ROWS);
        for (int i = 0; i < ROWS; i++) {
            std::cin >> grid[i];
        }

        std::string word = "";
        for (int col = 0; col < COLS; col++) {
            for (int row = 0; row < ROWS; row++) {
                if (grid[row][col] != '.') {
                    word += grid[row][col];
                }
            }
        }
        std::cout << word << std::endl;
    }

    return 0;
}
//
// Created by kozin on 02.10.2023.
//
