#include <algorithm>
#include <cmath>
#include <climits>
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <unordered_map>


int badness(const std::vector<int> & words_length, size_t begin, size_t end, int length_line) {
    int res = end - begin - 1;
    for (size_t i = begin; i != end; ++i) {
        res += words_length[i];
    }

    if (res > length_line) return INT_MAX;

    return std::pow(length_line - res, 2);
}


int main() {
    int N, L;
    scanf("%d%d", &N, &L);
    std::vector<int> words_length;
    char current_word[1000];

    for (size_t i = 0; i != N; ++i) {
        scanf("%s", current_word);
        words_length.push_back(strlen(current_word));
    }

    std::vector<long long> DP(N + 1, 0);
    std::vector<long long> line_breaks(N + 1, 0);

    for (size_t i = N - 1; i != -1; --i) {
        std::vector<long long> sums;
        for (size_t j = i + 1; j != N + 1; ++j) {
            int bad = badness(words_length, i, j, L);
            if (bad != INT_MAX) {
                sums.push_back(DP[j] + badness(words_length, i, j, L));
            } else {
                break
           }
        }
        auto min_ptr = std::min_element(sums.begin(), sums.end());
        DP[i] = *min_ptr;
        line_breaks[i] = std::distance(sums.begin(), min_ptr) + i + 1;
    }

    int cnt = 0;
    int i = 0;
    while (true) {
        cnt++;
        i = line_breaks[i];
        if (i == N) {
            std::cout << DP[0] << ' ' << cnt << std::endl;
            break;
        }
    }
}
