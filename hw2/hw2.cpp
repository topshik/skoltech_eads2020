#include <algorithm>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <utility>
#include <unordered_map>

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return (int) (hash1 ^ hash2) % (int) 1e7;
    }
};

int hash(std::pair<long long, long long> elem) {
    return ((long long) (elem.first) ^ (elem.second)) % ((int) 1e7);
}

class Dict {
private:
    std::vector<std::vector<std::pair<std::pair<long long, long long>, long long>>> dict;
public:
    Dict() : dict(1e7) {}

    std::vector<std::vector<std::pair<std::pair<long long, long long>, long long>>>::iterator end() {
        return dict.end();
    }

    bool erase(std::pair<long long, long long> key) {
        if (find(key) != NULL) {
            // dict[hash(key)].erase(dict[hash(key)].find(dict[hash(key)].begin(), dict[hash(key)].end(), key));
            std::pair<std::pair<long long, long long>, long long> elem = *find(key);
            dict[hash(key)].erase(std::find(dict[hash(key)].begin(), dict[hash(key)].end(), elem));
            return true;
        }
        return false;
    }

    std::pair<std::pair<long long, long long>, long long>* find(std::pair<long long, long long> key) {
        bool flag = false;
        int hash1 = hash(key);
        for (auto it = dict[hash1].begin(); it != dict[hash1].end(); ++it) {
            if ((*it).first == key) return &*it;
        }
        return NULL;
    }

    bool insert(std::pair<long long, long long> key, long long value) {
        if (find(key) == NULL) {
            dict[hash(key)].push_back(std::make_pair(key, value));
            return true;
        }
        return false;
    }
};

int main () {
    // std::cout << std::typeid((long long) 999999999999 % (int) 1e5) << std::endl;
    // Dict dict = Dict();
    // dict.insert(std::make_pair(1, 2), 3);

    // if (dict.find(std::make_pair(1, 3)) == NULL) {
    //     std::cout << "kekich" << std::endl;
    // }

    // std::cout << dict.insert(std::make_pair(1, 2), 4) << std::endl << dict.erase(std::make_pair(1, 2)) << std::endl << dict.insert(std::make_pair(1, 2), 4) << std::endl << (*(dict.find(std::make_pair(1, 2)))).second << std::endl;

    size_t num_lines;
    std::cin >> num_lines;

    bool flag;
    long long counter = 0;
    long long diameter = 0;
    // std::unordered_map<std::pair<long long, long long>, long long, hash_pair> cubes;
    Dict cubes = Dict();
    std::vector<long long> cube(3);
    for (size_t i = 0; i != num_lines; ++i) {
        flag = true;
        std::cin >> cube[0] >> cube[1] >> cube[2];
        std::sort(cube.begin(), cube.end());
        // auto find_surf1 = cubes.find(std::make_pair(cube[1], cube[2]));
        // auto find_surf2 = cubes.find(std::make_pair(cube[0], cube[2]));
        // auto find_surf3 = cubes.find(std::make_pair(cube[0], cube[1]));

        auto find_surf1 = cubes.find(std::make_pair(cube[1], cube[2]));
        auto find_surf2 = cubes.find(std::make_pair(cube[0], cube[2]));
        auto find_surf3 = cubes.find(std::make_pair(cube[0], cube[1]));


        // if (find_surf1 != cubes.end() && std::min(std::min(find_surf1->second + cube[0], cube[1]), cube[2]) > diameter) {
        //     diameter = std::min(std::min(find_surf1->second + cube[0], cube[1]), cube[2]);
        //     counter++;
        //     flag = false;
        //     if (find_surf1->second < cube[0]) cubes.erase(find_surf1);
        // } else if (find_surf2 != cubes.end() && std::min(std::min(find_surf2->second + cube[1], cube[0]), cube[2]) > diameter) {
        //     diameter = std::min(std::min(find_surf2->second + cube[1], cube[0]), cube[2]);
        //     counter++;
        //     flag = false;
        //     if (find_surf2->second < cube[1]) cubes.erase(find_surf2);
        // } else if (find_surf3 != cubes.end() && std::min(std::min(find_surf3->second + cube[2], cube[1]), cube[0]) > diameter) {
        //     diameter = std::min(std::min(find_surf3->second + cube[2], cube[1]), cube[0]);
        //     counter++;
        //     flag = false;
        //     if (find_surf3->second < cube[2]) cubes.erase(find_surf3);
        // }

        if (find_surf1 != NULL && std::min(std::min(find_surf1->second + cube[0], cube[1]), cube[2]) > diameter) {
            diameter = std::min(std::min(find_surf1->second + cube[0], cube[1]), cube[2]);
            counter++;
            flag = false;
            if (find_surf1->second < cube[0]) cubes.erase((*find_surf1).first);
        } else if (find_surf2 != NULL && std::min(std::min(find_surf2->second + cube[1], cube[0]), cube[2]) > diameter) {
            diameter = std::min(std::min(find_surf2->second + cube[1], cube[0]), cube[2]);
            counter++;
            flag = false;
            if (find_surf2->second < cube[1]) cubes.erase((*find_surf2).first);
        } else if (find_surf3 != NULL && std::min(std::min(find_surf3->second + cube[2], cube[1]), cube[0]) > diameter) {
            diameter = std::min(std::min(find_surf3->second + cube[2], cube[1]), cube[0]);
            counter++;
            flag = false;
            if (find_surf3->second < cube[2]) cubes.erase((*find_surf3).first);
        }

        if (cube[0] > diameter && flag) {
            diameter = cube[0];
            ++counter;
        }

        // cubes.insert({std::make_pair(cube[1], cube[2]), cube[0]});
        cubes.insert(std::make_pair(cube[1], cube[2]), cube[0]);
    }
    // std::cout << counter << ' ' << diameter << std::endl;
    std::cout << counter << std::endl;
}
