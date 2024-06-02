#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max(); // Representasi nilai tak hingga

// Fungsi untuk menjalankan algoritma Dijkstra
void dijkstra(int src, vector<vector<pair<int, int>>> &adj, vector<int> &dist, vector<int> &prev)
{
    int n = adj.size();
    dist.assign(n, INF);
    prev.assign(n, -1);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        for (const auto &edge : adj[u])
        {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

// Fungsi untuk membangun jalur dari source ke target
vector<int> build_path(int target, vector<int> &prev)
{
    vector<int> path;
    for (int at = target; at != -1; at = prev[at])
        path.push_back(at);
    reverse(path.begin(), path.end());
    return path;
}

int main()
{
    // Definisi graf
    int num_nodes = 6; // Misalnya kita punya 6 titik dalam graf
    vector<vector<pair<int, int>>> adj(num_nodes);

    // Misalnya kita tambahkan beberapa edge (u, v, w) di sini
    // Format: adj[u].push_back({v, w});
    adj[0].push_back({1, 10});
    adj[0].push_back({2, 15});
    adj[1].push_back({3, 12});
    adj[2].push_back({4, 10});
    adj[3].push_back({4, 2});
    adj[3].push_back({5, 1});
    adj[4].push_back({5, 5});

    int src = 0;  // Misalnya titik awal adalah 0 (UPI Cibiru)
    int dest = 5; // Misalnya titik tujuan adalah 5 (UPI Setiabudi)

    vector<int> dist;
    vector<int> prev;
    dijkstra(src, adj, dist, prev);

    // Mencetak jarak terpendek dari src ke dest
    cout << "Jarak terpendek dari " << src << " ke " << dest << " adalah " << dist[dest] << endl;

    // Membangun dan mencetak jalur terpendek
    vector<int> path = build_path(dest, prev);
    cout << "Jalur terpendek: ";
    for (int i = 0; i < path.size(); ++i)
    {
        if (i > 0)
            cout << " -> ";
        cout << path[i];
    }
    cout << endl;

    return 0;
}