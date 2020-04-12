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
    int mat, mismat, indel, trs;
    std::cin >> mat >> mismat >> indel >> trs;
    // int m, n;
    // std::cin >> m >> n;
    // std::string read, reference;
    // std::getline(std::cin, read);
    // std::getline(std::cin, reference);
    std::vector<std::vector<int>> table(m + 1);

    // init row and col
    for (size_t i = 0; i != n + 1; ++i) table[0].push_back(0);

    int kek = 0;
    for (size_t i = 1; i != m + 1) table[i].push_back(kek += indel);

    for (size_t i = 1; i != m + 1) std::cout << table[i][0];
}
