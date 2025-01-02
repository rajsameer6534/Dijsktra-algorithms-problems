#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>
#include <cmath>
#include <algorithm>
using namespace std;

void dijkstra(long long start, vector<vector<pair<long long, long long>>>& graph, vector<long long>& dist) {
    long long n = graph.size();
    dist.assign(n, LLONG_MAX);  // Initialize distances to infinity
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq;
    dist[start] = 0;  // Distance to start node is 0
    pq.push({0, start});
    
    while (!pq.empty()) {
        long long u = pq.top().second;
        long long d = pq.top().first;
        pq.pop();
        
        if (d > dist[u]) continue;  // Skip if this distance is outdated
        
        for (auto edge : graph[u]) {
            long long v = edge.first;       // Neighbor node
            long long cost = edge.second;  // Edge cost
            
            if (dist[v] > dist[u] + cost) {  // Relax the edge
                dist[v] = dist[u] + cost;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    long long n, m;
    cin >> n >> m;
    
    // Adjacency list for the graph and reverse graph
    vector<vector<pair<long long, long long>>> graph(n + 1), reverseGraph(n + 1);
    
    for (long long i = 0; i < m; i++) {
        long long a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});         // Original graph
        reverseGraph[b].push_back({a, c});  // Reverse graph
    }
    
    vector<long long> distFromStart, distToEnd;
    
    // Perform Dijkstra's algorithm from the start (1) and the end (n)
    dijkstra(1, graph, distFromStart);
    dijkstra(n, reverseGraph, distToEnd);
    
    long long result = LLONG_MAX;
    
    // Try applying the discount to each edge
    for (long long u = 1; u <= n; u++) {
        for (auto edge : graph[u]) {
            long long v = edge.first;
            long long cost = edge.second;
            
           
            if (distFromStart[u] != LLONG_MAX && distToEnd[v] != LLONG_MAX) {
                // Calculate the total cost with the discount applied to this edge
                result = min(result, distFromStart[u] + (cost / 2) + distToEnd[v]);
            }
        }
    }
    
   
    cout << result << endl;
    return 0;
}
