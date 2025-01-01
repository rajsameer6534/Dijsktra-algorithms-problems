#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

vector<long long> dijkstra(int n, vector<vector<pair<int, int>>>& adj) {
    // Distance and parent arrays
    vector<long long> dis(n + 1, LLONG_MAX);
    vector<int> parent(n + 1);

    // Min-heap (priority queue) to store {distance, node}
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    // Initialization for source node
    dis[1] = 0;
    parent[1] = 1; // Parent of the source is itself
    pq.push({0, 1}); // {distance, node}

    while (!pq.empty()) {
        long long curr_dis = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        // If current distance is outdated, skip
        if (curr_dis > dis[node]) continue;

        // Relaxation for all adjacent nodes
        for (auto& edge : adj[node]) {
            int adjnode = edge.first;
            int weight = edge.second;

            if (dis[adjnode] > curr_dis + weight) {
                dis[adjnode] = curr_dis + weight;
                parent[adjnode] = node;
                pq.push({dis[adjnode], adjnode});
            }
        }
    }

    // If there's no path to node `n`, return -1
    if (dis[n] == LLONG_MAX) return {-1};

    // Reconstruct the path from 1 to n
    vector<long long> path;
    for (int v = n; v != parent[v]; v = parent[v]) {
        path.push_back(v);
    }
    path.push_back(1);
    reverse(path.begin(), path.end());

    return path;
}

int main() {
    int n, m;
    cin >> n >> m;

    // Adjacency list for storing the graph
    vector<vector<pair<int, int>>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w}); // Since the graph is undirected
    }

    // Get the shortest path from Syrjälä (city 1) to city n
    vector<long long> path = dijkstra(n, adj);

    // Print the result
    if (path.size() == 1 && path[0] == -1) {
        cout << -1 << endl; // No path exists
    } else {
        for (long long node : path) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
