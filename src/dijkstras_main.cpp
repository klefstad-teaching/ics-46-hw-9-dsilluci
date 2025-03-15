#include "dijkstras.h"
int main() {
    Graph G;
    ifstream in("src/small.txt");
    in >> G;
    vector<int> prev(G.numVertices);
    vector<int> dist = dijkstra_shortest_path(G, 0, prev);
    vector<int> p0 = extract_shortest_path(dist, prev, 0);
    vector<int> p1 = extract_shortest_path(dist, prev, 1);
    vector<int> p2 = extract_shortest_path(dist, prev, 2);
    vector<int> p3 = extract_shortest_path(dist, prev, 3);
    print_path(p0, dist[0]);
    print_path(p1, dist[1]);
    print_path(p2, dist[2]);
    print_path(p3, dist[3]);
}