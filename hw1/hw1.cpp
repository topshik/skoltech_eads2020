#include <climits>
#include <iostream>
#include <set>
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

    std::vector<long long> dijkstra2(bool forward, long long d) {
        std::vector<long long> dist(vertices_number, UINT_MAX);
        std::set<Vertex> vertices_to_add;
        std::vector<long long> res;

        (forward ? dist[source] = 0 : dist[target] = 0);
        (forward ? vertices_to_add.insert(Vertex(source, 0)) : vertices_to_add.insert(Vertex(target, 0)));

        while (!vertices_to_add.empty()) {
            Vertex shortest_vertex = *vertices_to_add.begin();
            vertices_to_add.erase(vertices_to_add.begin());
            long long cur_vertex = shortest_vertex.vertex;
            long long cur_dist = shortest_vertex.path_length;
            res.push_back(cur_dist);

            if ((cur_vertex == target) && forward && cur_dist <= d) {
                path_exists = true;
                break;
            }

            for (auto neighbour : (forward ? forward_graph[cur_vertex] : backward_graph[cur_vertex])) {
                long long neighbour_vertex = neighbour.first;
                long long neighbour_weight = neighbour.second;

                if (cur_dist + neighbour_weight < dist[neighbour_vertex]) {
                    vertices_to_add.erase(Vertex(neighbour_vertex, dist[neighbour_vertex]));
                    dist[neighbour_vertex] = cur_dist + neighbour_weight;
                    vertices_to_add.insert(Vertex(neighbour_vertex, dist[neighbour_vertex]));
                }
            }
        }
        return res;
    }

    // std::vector<long long> dijkstra(bool forward, long long d) {
    //     std::vector<long long> dist(vertices_number, -1);
    //     std::vector<long long> res;
    //     std::vector<bool> closed(vertices_number, false);
    //     std::set<Vertex> vertices_to_add;

    //     (forward ? dist[source] = 0 : dist[target] = 0);

    //     (forward ? vertices_to_add.insert(Vertex(source, 0)) : vertices_to_add.insert(Vertex(target, 0)));

    //     while(!vertices_to_add.empty()) {
    //         // pick new vertex
    //         Vertex shortest_vertex = *vertices_to_add.begin();
    //         vertices_to_add.erase(vertices_to_add.begin());
    //         closed[shortest_vertex.vertex] = true;

    //         // stopping criteria
    //         // if (dist[shortest_vertex.number] > d) break;

    //         if (forward && (shortest_vertex.vertex == target) && shortest_vertex.path_length <= d) {
    //             path_exists = true;
    //             break;
    //         }

    //         res.push_back(shortest_vertex.path_length);

    //         // update new neighbours values
    //         for (auto neighbour : (forward ? forward_graph[shortest_vertex.vertex] : backward_graph[shortest_vertex.vertex])) {
    //             // neighbour - map element: neighbour.first = vertex_number, neighbour.second = edge_weight
    //             if (!closed[neighbour.first]) {
    //                 // std::cout << "Processing neighbour " << neighbour.first << std::endl;
    //                 if ((dist[shortest_vertex.vertex] + neighbour.second < dist[neighbour.first]) && (dist[neighbour.first] != -1)) {
    //                     vertices_to_add.erase(Vertex(neighbour.first, dist[neighbour.first]));
    //                     // std::cout << "Vertex erased: " << neighbour.first << ' ' << dist[neighbour.first] << std::endl;
    //                 }

    //                 dist[neighbour.first] = dist[shortest_vertex.vertex] + neighbour.second;
    //                 vertices_to_add.insert(Vertex(neighbour.first, dist[neighbour.first]));
    //             }
    //         }
    //     }
    //     return res;
    // }
};

int main () {
    // input processing
    long long n, m, from, to, weight, s, t, d;
    long long res = 0;

    std::cin >> n >> m;

    Graph graph(n);

    for (long long i = 0; i != m; ++i) {
        std::cin >> from >> to >> weight;
        graph.add_edge(from - 1, to - 1, weight);
    }

    std::cin >> s >> t >> d;
    graph.init_s_t(s - 1, t - 1);
    // end input processing

    std::vector<long long> forward_candidates;
    forward_candidates = graph.dijkstra2(true, d);

    if  (graph.path_exists) {
        std::cout << n * (n - 1) << std::endl;
        return 0;
    }

    std::vector<long long> backward_candidates;
    backward_candidates = graph.dijkstra2(false, d);

    // degug
    // std::cout << std::endl;
    // for (long long i = 0; i != forward_candidates.size(); ++i) {
    //     std::cout << forward_candidates[i] << ' ';
    // }
    // std::cout << std::endl;
    // for (long long i = 0; i != backward_candidates.size(); ++i) {
    //     std::cout << backward_candidates[i] << ' ';
    // }
    // std::cout << std::endl;
    // end debug

    long long j = backward_candidates.size() - 1;
    for (long long i = 0; i != forward_candidates.size(); ++i) {
        while ((forward_candidates[i] + backward_candidates[j] + 1 > d) && j >= 0) {
            j--;
        }
        res += j + 1;
    }

    std::cout << res << std::endl;
}
