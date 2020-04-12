#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

int main () {
    size_t num_lines;
    std::cin >> num_lines;

    int counter = 0;
    long long diameter = 0;
    std::unordered_map<std::pair<int, int>, int, hash_pair> cubes;
    std::vector<int> cube(3);
    for (size_t i = 0; i != num_lines; ++i) {
        std::cin >> cube[0] >> cube[1] >> cube[2];
        std::sort(cube.begin(), cube.end());
        // std::cout << "Got new elem" << std::endl;
        if (cube[0] > diameter) {
            diameter = cube[0];
            ++counter;
        } else {
            auto find_surf1 = cubes.find(std::make_pair(cube[0], cube[1]));
            auto find_surf2 = cubes.find(std::make_pair(cube[0], cube[2]));
            auto find_surf3 = cubes.find(std::make_pair(cube[1], cube[2]));
            if (find_surf1 != cubes.end() && std::min(std::min(find_surf1->second + cube[2], cube[0]), cube[1]) > diameter) {
                diameter = find_surf1->second + cube[2];
                counter++;
                // if (find_surf1->second > cube[2]) find_surf2->second = cube[2];
            } else {
                if (find_surf2 != cubes.end() && std::min(std::min(find_surf2->second + cube[1], cube[0]), cube[2]) > diameter) {
                    diameter = find_surf2->second + cube[1];
                    counter++;
                    // if (find_surf1->second > cube[1]) find_surf2->second = cube[1];
                } else {
                    if (find_surf3 != cubes.end() && std::min(std::min(find_surf3->second + cube[0], cube[1]), cube[2]) > diameter) {
                        diameter = find_surf3->second + cube[0];
                        counter++;
                        // if (find_surf1->second > cube[0]) find_surf2->second = cube[0];
                    }
                }
            }
        }
        cubes.insert({std::make_pair(cube[1], cube[2]), cube[0]});
    }
    std::cout << counter << std::endl;
}
close
