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
    int mat, mismat, indel, trs, m, n, score1, score2, score3, current_score, upper_left;
    std::string read;
    char ref_char;
    std::cin >> mat >> mismat >> indel >> trs >> m >> n;
    std::cin >> read;
    std::vector<std::vector<int>> table(m + 1);
    std::vector<int> curr_col;
    int kek = 0;
    for (size_t i = 0; i != m + 1; ++i) curr_col.push_back(kek += indel);

    for (size_t j = 0; j != n ; ++j) {
        std::cin >> ref_char;
        upper_left = 0;
        for (size_t i = 0; i != m ; ++i) {
            score1 = upper_left + (read[i] == ref_char ? mat : mismat);
            score2 = (i != 0 ? curr_col[i - 1] : 0) + indel;
            score3 = curr_col[i] + indel;

            current_score = std::max({score1, score2, score3});
            upper_left = curr_col[i];
            curr_col[i] = current_score;
            if (current_score >= trs && i == m - 1) {
                std::cout << j + 1 << ' ' << current_score << std::endl;
            }
        }
    }
}
