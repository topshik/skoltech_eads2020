#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <unordered_map>

struct Vertex {
public:
    long long vertex, path_length;

    Vertex(){};

    Vertex(long long num, long long dist) : vertex(num), path_length(dist) {}

    bool operator<(const Vertex &other) const {
        if (path_length == other.path_length) return vertex < other.vertex;
        return path_length < other.path_length;
    }
};

class Graph {
private:
    long long vertices_number, source, target;
    std::unordered_map<long long, std::unordered_map<long long, long long>> forward_graph;
    std::unordered_map<long long, std::unordered_map<long long, long long>> backward_graph;

public:
    bool path_exists = false;

    Graph() {};

    Graph(int n) {
        vertices_number = n;
    }

    void init_s_t(long long s, long long t) {
        source = s;
        target = t;
    }

    void add_edge(long long from, long long to, long long weight) {
        forward_graph[from][to] = weight;
        backward_graph[to][from] = weight;
    }

    std::vector<long long> dijkstra2() {
        std::vector<long long> dist(vertices_number, -1);
        std::set<Vertex> vertices_to_add;
        std::vector<long long> res;

        // (forward ? dist[source] = 0 : dist[target] = 0);
        // (forward ? vertices_to_add.insert(Vertex(source, 0)) : vertices_to_add.insert(Vertex(target, 0)));

        dist[source] = 0;
        vertices_to_add.insert(Vertex(source, 0));

        while (!vertices_to_add.empty()) {
            Vertex shortest_vertex = *vertices_to_add.begin();
            vertices_to_add.erase(vertices_to_add.begin());
            long long cur_vertex = shortest_vertex.vertex;
            long long cur_dist = shortest_vertex.path_length;
            res.push_back(cur_dist);

            // for (auto neighbour : (forward ? forward_graph[cur_vertex] : backward_graph[cur_vertex])) {
            for (auto neighbour : forward_graph[cur_vertex]) {
                long long neighbour_vertex = neighbour.first;
                long long neighbour_weight = neighbour.second;

                if (cur_dist + neighbour_weight < dist[neighbour_vertex]) {
                    std::cout << neighbour_vertex << std::endl;
                    vertices_to_add.erase(Vertex(neighbour_vertex, dist[neighbour_vertex]));
                    dist[neighbour_vertex] = cur_dist + neighbour_weight;
                    vertices_to_add.insert(Vertex(neighbour_vertex, dist[neighbour_vertex]));
                }
            }
        }
        return dist;
    }
};

int main () {
    // input processing
    long long n, s, f;
    long long res = 0;

    std::cin >> n >> s >> f;

    Graph graph(n);

    long long current_weight;

    for (long long i = 0; i != n; ++i) {
        for (long long j = 0; j != n; ++j) {
            std::cin >> current_weight;
            if (current_weight == -1 || i == j) continue;
            graph.add_edge(i, j, current_weight);
            // std::cout << i << ' ' << j << ' ' << current_weight << std::endl;
        }
    }

    graph.init_s_t(s - 1, f - 1);
    // end input processing

    std::vector<long long> distances;
    distances = graph.dijkstra2();

    // std::cout << std::endl;
    // for (auto elem : distances) std::cout << elem << ' ';
    // std::cout << std::endl;

    std::cout << distances[f - 1] << std::endl;
}
