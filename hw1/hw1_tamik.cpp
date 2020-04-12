#include <algorithm>
#include <climits>
#include <iostream>
#include <set>
#include <vector>

using ll = long long;
using vertex = std::pair<ll, ll>;
using graph = std::vector<std::vector<vertex>>;

std::pair<graph, graph> read_graphs(ll n, ll m) {
    graph forward_graph(n);
    graph backward_graph(n);

    for (ll i = 0; i < m; ++i) {
        ll a, b, w;
        std::cin >> a >> b >> w;
        forward_graph[a-1].push_back(vertex(b-1, w));
        backward_graph[b-1].push_back(vertex(a-1, w));
    }
    return std::make_pair(forward_graph, backward_graph);
}

std::pair<std::vector<ll>, std::vector<ll>> dijkstra(graph g, ll s) {
    std::vector<ll> result;

    std::vector<ll> dists(g.size(), LLONG_MAX);
    std::set<std::pair<ll, ll>> unused;
    dists[s] = 0;
    unused.insert(std::make_pair(0, s));
    for (ll i = 0; i < g.size(); ++i) {
        if (i != s) {
            unused.insert(std::make_pair(LLONG_MAX, i));
        }
    }
    while (!unused.empty() && unused.begin()->first != LLONG_MAX) {
        std::pair<ll, ll> cur_pair = *unused.begin();
        unused.erase(unused.begin());
        ll cur_dist = cur_pair.first;
        ll cur_vertex = cur_pair.second;
        result.push_back(cur_dist);
        for (auto neighbour_pair : g[cur_vertex]) {
            ll neighbour_vertex = neighbour_pair.first;
            ll neighbour_weight = neighbour_pair.second;
            if (cur_dist + neighbour_weight < dists[neighbour_vertex]) {
                unused.erase(std::make_pair(dists[neighbour_vertex], neighbour_vertex));
                unused.insert(std::make_pair(cur_dist + neighbour_weight, neighbour_vertex));
                dists[neighbour_vertex] = cur_dist + neighbour_weight;
            }
        }
    }

    return std::make_pair(dists, result);
}

int main() {
    std::pair<graph, graph> graphs;
    ll n, m;
    ll s, t, d;
    ll loops = 0;
    ll result = 0;

    std::cin >> n >> m;
    graphs = read_graphs(n, m);
    std::cin >> s >> t >> d;
    s--; t--;

    auto [fd, fd_sorted] = dijkstra(graphs.first, s);  // forward distances
    auto [bd, bd_sorted] = dijkstra(graphs.second, t);  // backward distances

    if (s == t ||
        fd[t] <= d) {  //  the path already exists
        std::cout << n * (n - 1) << std::endl;
        return 0;
    }

    for (ll i = 0, j = bd_sorted.size() - 1; i != fd_sorted.size(); ++i) {
        while (j >= 0 &&
               (fd_sorted[i] == LLONG_MAX ||
                bd_sorted[j] == LLONG_MAX ||
                fd_sorted[i] + bd_sorted[j] + 1 > d)) {
            j--;
        }
        result += j + 1;
    }

    result -= loops;
    std::cout << result << std::endl;

    return 0;
}
