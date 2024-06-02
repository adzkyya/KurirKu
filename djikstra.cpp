#include <iostream>

using namespace std;

const int INF = 1000000; // Representasi nilai tak hingga yang cukup besar
const int MAX_NODES = 6; // Maksimum jumlah node

// Fungsi untuk mencari index dari node dengan jarak minimum yang belum diproses
int minDistance(int dist[], bool sptSet[])
{
    int min = INF, min_index;

    for (int v = 0; v < MAX_NODES; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Fungsi untuk mencetak jalur terpendek
void printPath(int prev[], int j)
{
    if (prev[j] == -1)
        return;
    printPath(prev, prev[j]);
    cout << " -> " << j;
}

// Fungsi untuk mencetak jarak terpendek
void printSolution(int dist[], int prev[], int src, int dest)
{
    cout << "Jarak terpendek dari " << src << " ke " << dest << " adalah " << dist[dest] << endl;
    cout << "Jalur terpendek: " << src;
    printPath(prev, dest);
    cout << endl;
}

// Fungsi untuk menjalankan algoritma Dijkstra
void dijkstra(int graph[MAX_NODES][MAX_NODES], int src, int dest)
{
    int dist[MAX_NODES];
    bool sptSet[MAX_NODES];
    int prev[MAX_NODES];

    for (int i = 0; i < MAX_NODES; i++)
    {
        dist[i] = INF;
        sptSet[i] = false;
        prev[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < MAX_NODES - 1; count++)
    {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < MAX_NODES; v++)
        {
            if (!sptSet[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                prev[v] = u;
            }
        }
    }

    printSolution(dist, prev, src, dest);
}

int main()
{
    int graph[MAX_NODES][MAX_NODES] = {
        {0, 10, 15, 0, 0, 0},
        {0, 0, 0, 12, 0, 0},
        {0, 0, 0, 0, 10, 0},
        {0, 0, 0, 0, 2, 1},
        {0, 0, 0, 0, 0, 5},
        {0, 0, 0, 0, 0, 0}};

    int src = 0;  // Misalnya titik awal adalah 0 (UPI Cibiru)
    int dest = 5; // Misalnya titik tujuan adalah 5 (UPI Setiabudi)

    dijkstra(graph, src, dest);

    return 0;
}
