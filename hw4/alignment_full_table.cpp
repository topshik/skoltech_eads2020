#include <algorithm>
#include <cmath>
#include <climits>
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <unordered_map>

int main() {
    // maximum score for each position isn't implemented
    int mat, mismat, indel, trs, m, n;
    std::string read;
    char ref_char;
    std::cin >> mat >> mismat >> indel >> trs >> m >> n;
    std::cin >> read;
    std::vector<std::vector<int>> table(m + 1);

    // init row and col
    int kek = -indel;
    for (size_t i = 0; i != m + 1; ++i) table[i].push_back(kek += indel);
    for (size_t i = 1; i != n + 1; ++i) table[0].push_back(0);

    int score1, score2, score3, current_score;
    for (size_t j = 1; j != n + 1; ++j) {
        std::cin >> ref_char;
        for (size_t i = 1; i != m + 1; ++i) {
            score1 = table[i - 1][j - 1] + (read[i - 1] == ref_char ? mat : mismat);
            score2 = table[i - 1][j] + indel;
            score3 = table[i][j - 1] + indel;
            current_score = std::max({score1, score2, score3});
            table[i].push_back(current_score);
            if (current_score >= trs && i == m) {
                std::cout << j << ' ' << current_score << std::endl;
            }
        }
    }

    // debug table
    std::cout << std::endl << "Debug table: " << std::endl;
    for (size_t i = 0; i != m + 1; ++i) {
        if (i != 0) std::cout << read[i - 1] << ' ';
        if (i == 0) std::cout << "  ";
        for (size_t j = 0; j != n + 1; ++j) {
            std::cout << table[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}
