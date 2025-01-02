#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>
#include <cmath>
#include <algorithm>
using namespace std;

const long long MOD = 1e9+7;

void solve() {
    long long n, m;
    cin >> n >> m;

    vector<vector<pair<long long, long long>>> adj(n + 1);
    for (long long i = 0; i < m; i++) {
        long long a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    // Dijkstra's algorithm
    vector<long long> dist(n + 1, LLONG_MAX);
    vector<long long> ways(n + 1, 0);
    vector<long long> minEdges(n + 1, LLONG_MAX);
    vector<long long> maxEdges(n + 1, LLONG_MIN);

    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq;

    dist[1] = 0;
    ways[1] = 1;
    minEdges[1] = 0;
    maxEdges[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        long long node=pq.top().second;
        long long curr_dis=pq.top().first;
        pq.pop();

        if (curr_dis > dist[node]) continue;

        for (auto it : adj[node]) {
            long long adjnode=it.first;
            long long edgeweight=it.second;
            if (dist[adjnode] > dist[node] + edgeweight) {
                dist[adjnode] = dist[node] + edgeweight;
                pq.push({dist[adjnode], adjnode});

                ways[adjnode] = ways[node];
                minEdges[adjnode] = minEdges[node] + 1;
                maxEdges[adjnode] = maxEdges[node] + 1;
            } else if (dist[adjnode] == dist[node] + edgeweight) {
                ways[adjnode] = (ways[adjnode] + ways[node]) % MOD;
                minEdges[adjnode] = min(minEdges[adjnode], minEdges[node] + 1);
                maxEdges[adjnode] = max(maxEdges[adjnode], maxEdges[node] + 1);
            }
        }
    }

    cout << dist[n] << " " << ways[n] << " " << minEdges[n] << " " << maxEdges[n] << endl;
}

int main() {
    solve();
    return 0;
}
