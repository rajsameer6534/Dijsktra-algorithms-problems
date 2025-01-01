// cses:-https://cses.fi/problemset/task/1671/
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

vector<long long> shortestPath(long long n, long long m, vector<vector<pair<long long, long long>>>& adj) {
    vector<long long> dis(n + 1,LLONG_MAX); 
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq; // Min-heap

    // Start from city 1
    dis[1] = 0;
    pq.push({0, 1}); // distance, node

    while (!pq.empty()) {
        long long curr_dis = pq.top().first;
        long long node = pq.top().second;
        pq.pop();

        // Skip outdated distance entries in the priority queue
        if (curr_dis > dis[node]) continue;

        // Process adjacent nodes
        for (auto& it : adj[node]) {
            long long adjnode = it.first;
            long long edgeweight = it.second;

            // Relaxation condition
            if (curr_dis + edgeweight < dis[adjnode]) {
                dis[adjnode] = curr_dis + edgeweight;
                pq.push({dis[adjnode], adjnode});
            }
        }
    }

    return dis;
}

int main() {
    long long n, m;
    cin >> n >> m;

    // Adjacency list for storing the graph
    vector<vector<pair<long long, long long>>> adj(n + 1);

    for (long long i = 0; i < m; i++) {
        long long a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    // Get the shortest paths from Syrjälä (city 1)
    vector<long long> result = shortestPath(n, m, adj);

    // Prlong long results for all cities from 1 to n
    for (long long i = 1; i <= n; i++) {
        cout << result[i] << " ";
    }

    return 0;
}
