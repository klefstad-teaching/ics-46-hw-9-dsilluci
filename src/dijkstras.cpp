#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int> &previous) {
    // int num_vertices = G.numVertices;
    // vector<int> distances(num_vertices, INF);
    // vector<bool> visited(num_vertices, false);
    // distances[source] = 0;
    // previous[source] = -1;
    // priority_queue<pair<int,int>> min_heap; // pair<vertex, weight>
    // min_heap.push({source, 0});
    // while (!min_heap.empty()) {
    //     int u = min_heap.top().first;
    //     min_heap.pop();
    //     if (visited[u]) continue;
    //     visited[u] = true;
    //     for (Edge edge : G[u]) {
    //         int v = edge.dst;
    //         int weight = edge.weight;
    //         if (!visited[v] && distances[u] + weight < distances[v]) {
    //             distances[v] = distances[u] + weight;
    //             previous[v] = u;
    //             min_heap.push({v, distances[v]});
    //         }
    //     }
    // }
    // return distances;
    int n = G.numVertices;
    previous.assign(n, -1);
    vector<int> distances(n, INF);
    vector<bool> visited(n, false);

    priority_queue<pair<int,int>> pq;
    pq.push({source, 0});
    distances[source] = 0;
    while (!pq.empty()) {
        int u = pq.top().first;
        pq.pop();
        if (visited[u])
            continue;
        for (Edge neighbor : G[u]) {
            int v = neighbor.dst;
            int weight = neighbor.weight;
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push({v, distances[v]});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int> &distances, const vector<int> &previous, int destination) {
    vector<int> shortest_path;
    for (int curr = destination; curr != -1; curr = previous[curr])
        shortest_path.push_back(curr);
    reverse(shortest_path.begin(), shortest_path.end());
    return shortest_path;
}

void print_path(const vector<int> &v, int total) {
    // how would I know the total here? just distances[dst]?
    for (int x : v)
        cout << x << " ";
    cout << endl << "Total cost is " << total << endl;
}