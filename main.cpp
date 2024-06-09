#include <iostream>
using namespace std;

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <limits.h>
#include <stack>
#include <string>
#include <cstring>
#include <climits>

using namespace std;
// Fitur Nomer 1
// Struktur untuk menyimpan informasi graf
struct Graph
{
    unordered_map<string, unordered_map<string, int>> adjList;
};

// Fungsi untuk menambahkan edge ke dalam graf
void addEdge(Graph &graph, const string &u, const string &v, int weight)
{
    graph.adjList[u][v] = weight;
    graph.adjList[v][u] = weight;
}

// Algoritma Dijkstra untuk mencari jarak terpendek
unordered_map<string, int> dijkstra(const Graph &graph, const string &start, unordered_map<string, string> &previous)
{
    unordered_map<string, int> distances;
    for (auto &pair : graph.adjList)
    {
        distances[pair.first] = INT_MAX;
    }
    distances[start] = 0;

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    pq.push({0, start});

    while (!pq.empty())
    {
        int currentDistance = pq.top().first;
        string currentNode = pq.top().second;
        pq.pop();

        for (const auto &neighbor : graph.adjList.at(currentNode))
        {
            string neighborNode = neighbor.first;
            int weight = neighbor.second;
            int distance = currentDistance + weight;

            if (distance < distances[neighborNode])
            {
                distances[neighborNode] = distance;
                pq.push({distance, neighborNode});
                previous[neighborNode] = currentNode;
            }
        }
    }

    return distances;
}

// Fungsi untuk mencetak jalur dari start ke end
void printPath(const unordered_map<string, string> &previous, const string &start, const string &end)
{
    stack<string> path;
    string current = end;

    while (current != start)
    {
        path.push(current);
        current = previous.at(current);
    }
    path.push(start);

    while (!path.empty())
    {
        cout << path.top();
        path.pop();
        if (!path.empty())
        {
            cout << " -> ";
        }
    }
    cout << endl;
}

// Fitur nomer 2
// fitur untuk mengelompokkan barang berdasarkan lokasi dan tujuan
struct infoBarang
{
    string lokasi;
    string tujuan;
    string berkas;
};

struct TreeNode
{
    string lokasi;
    string tujuan;
    queue<string> berkas;
    TreeNode *kiri;
    TreeNode *kanan;

    TreeNode(string loc, string dest) : lokasi(loc), tujuan(dest), kiri(nullptr), kanan(nullptr) {}
};

// Fungsi untuk memasukkan berkas baru ke dalam BST
TreeNode *masukkanBerkas(TreeNode *root, const string &lokasi, const string &tujuan, const string &berkas)
{
    if (root == nullptr)
    {
        root = new TreeNode(lokasi, tujuan);
        root->berkas.push(berkas);
    }
    else if (lokasi < root->lokasi || (lokasi == root->lokasi && tujuan < root->tujuan))
    {
        root->kiri = masukkanBerkas(root->kiri, lokasi, tujuan, berkas);
    }
    else if (lokasi > root->lokasi || (lokasi == root->lokasi && tujuan > root->tujuan))
    {
        root->kanan = masukkanBerkas(root->kanan, lokasi, tujuan, berkas);
    }
    else
    {
        root->berkas.push(berkas);
    }

    return root;
}

// Fungsi untuk melakukan traversal in-order pada BST dan mencetak berkas yang dikelompokkan berdasarkan lokasi
void inorderTraversal(TreeNode *root)
{
    if (root != nullptr)
    {
        inorderTraversal(root->kiri);
        cout << "-------------------------------------" << endl;
        cout << "Lokasi: " << root->lokasi << endl;
        cout << "Tujuan: " << root->tujuan << endl;
        cout << "Berkas: ";
        queue<string> tempQueue = root->berkas;
        while (!tempQueue.empty())
        {
            cout << tempQueue.front() << " ";
            tempQueue.pop();
        }
        cout << endl;
        inorderTraversal(root->kanan);
    }
}

// Fitur nomer 3
const int MAX_V = 100;
const int INF = INT_MAX;

int V;                 // Jumlah simpul
int adj[MAX_V][MAX_V]; // Matriks ketetanggaan
bool visited[MAX_V];   // Array untuk mengecek simpul yang sudah dikunjungi

void inisialisasiGraf(int simpul)
{
    V = simpul;
    memset(adj, INF, sizeof(adj));
    for (int i = 0; i < V; ++i)
        adj[i][i] = 0; // Jarak ke diri sendiri adalah 0
}

void tambahEdge(int u, int v, int w)
{
    adj[u][v] = w;
    adj[v][u] = w;
}

void bfs(int mulai)
{
    bool queue[MAX_V];
    int depan = 0, belakang = 0;
    memset(queue, false, sizeof(queue));

    queue[belakang++] = mulai;
    visited[mulai] = true;

    while (depan < belakang)
    {
        int u = queue[depan++];
        for (int v = 0; v < V; ++v)
        {
            if (adj[u][v] != INF && !visited[v])
            {
                visited[v] = true;
                queue[belakang++] = v;
            }
        }
    }
}

bool terhubung()
{
    memset(visited, false, sizeof(visited));
    bfs(0);

    for (int i = 0; i < V; ++i)
    {
        if (!visited[i])
            return false;
    }

    return true;
}

int jarakMin(int dist[], bool sptSet[])
{
    int min = INF, min_index;
    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void dijkstra(int src, int dest, int parent[])
{
    int dist[MAX_V];
    bool sptSet[MAX_V];

    for (int i = 0; i < V; i++)
        dist[i] = INF, sptSet[i] = false, parent[i] = -1;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        int u = jarakMin(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && adj[u][v] != INF && dist[u] != INF && dist[u] + adj[u][v] < dist[v])
            {
                dist[v] = dist[u] + adj[u][v];
                parent[v] = u;
            }
    }
}

int lacakBarang(int src, int dest, int waktuBerlalu)
{
    if (!terhubung())
    {
        cout << "Graf tidak terhubung." << endl;
        return -1;
    }

    int parent[MAX_V];
    dijkstra(src, dest, parent);

    int path[MAX_V];
    int path_len = 0;
    for (int v = dest; v != -1; v = parent[v])
        path[path_len++] = v;

    int waktuTerpakai = 0;

    for (int i = path_len - 1; i > 0; --i)
    {
        int u = path[i];
        int v = path[i - 1];
        waktuTerpakai += adj[u][v];
        if (waktuTerpakai > waktuBerlalu)
        {
            return u;
        }
    }

    return dest; // Barang telah mencapai tujuan
}

// Fitur nomer 4
struct Node
{
    string lokasi;
    int waktu; // waktu dalam menit
    vector<Node *> children;
};

// untuk membuat node baru
Node *createNode(string lokasi, int waktu)
{
    Node *newNode = new Node;
    newNode->lokasi = lokasi;
    newNode->waktu = waktu;
    return newNode;
}

// untuk menambahkan anak ke node
void tambahAnak(Node *parent, Node *child)
{
    parent->children.push_back(child);
}

// untuk menampilkan estimasi waktu
void estimasi(Node *node, int accumulatedTime, int &counter)
{
    accumulatedTime += node->waktu;
    cout << counter++ << ". Lokasi: " << node->lokasi << ", Estimasi Waktu: " << accumulatedTime << " menit" << endl;

    for (Node *child : node->children)
    {
        estimasi(child, accumulatedTime, counter);
    }
}

// Fitur nomer 5
// Struktur untuk menyimpan informasi pengirim dan penerima
struct info
{
    string namaPengirim;
    string alamatPengirim;
    string kontakPengirim;
    string namaPenerima;
    string alamatPenerima;
    string kontakPenerima;
    string nomorResi;
    string tglKirim;
    float beratBarang;
};

// Fitur nomer 6
void displayQueue(const queue<tuple<string, string, string>>& inputQueue) {
    if (inputQueue.empty()) {
        cout << "Tidak Terdapat Antrian Berkas" << endl;
        return;
        }

    queue<tuple<string, string, string>> tempQueue(inputQueue);
    
    while (!tempQueue.empty()) {
        string location, destination, file;
        tie(location, destination, file) = tempQueue.front(); 
        tempQueue.pop();
        cout << "Berkas: " << file << endl;
        cout << "Tujuan: " << destination << endl;
        cout << "Lokasi: " << location << endl;
        cout << "----------------" << endl;
    }
}

int main()
{
    // fitur upi file express
    // 1. rute terpendek antar kampus
    // 2. ⁠pengelompokkan barang berdasarkan lokasi
    // 3. ⁠pelacakan barang
    // 4. ⁠estimasi waktu sampai
    // 5. ⁠resi barang
    // 6. pengelolaan antrian pengiriman
    queue<tuple<string, string, string>> inputQueue;
    int pilihan;
    string border = "============================================";
    string welcome = "SELAMAT DATANG DI APLIKASI UPI FILE EXPRESS";

    do
    {
        cout << border << "\n"
             << welcome << "\n"
             << border << endl;
        cout << "1. Pencarian Rute Tercepat\n2. Pengelompokkan Barang Berdasarkan Lokasi\n3. Pelacakan Barang\n4. Estimasi Waktu Sampai\n5. Resi Barang\n6. Pengelolaan Antrian Pengiriman\n7. Exit\n"
             << border << "\nMasukkan Pilihan Anda: ";
        cin >> pilihan;
        if (pilihan == 1)
        {
            cout << border << endl;
            Graph graph;
            int numEdges;
            cout << "Masukkan jumlah edge: ";
            cin >> numEdges;

            cout << "Masukkan edge dalam format: vertex1 vertex2 bobot" << endl;
            for (int i = 0; i < numEdges; ++i)
            {
                string u, v;
                int weight;
                cin >> u >> v >> weight;
                addEdge(graph, u, v, weight);
            }

            string start, end;
            cout << "Masukkan vertex awal: ";
            cin >> start;
            cout << "Masukkan vertex tujuan: ";
            cin >> end;

            unordered_map<string, string> previous;
            unordered_map<string, int> distances = dijkstra(graph, start, previous);

            if (distances[end] != INT_MAX)
            {
                cout << "Jarak terpendek dari " << start << " ke " << end << " adalah " << distances[end] << " Kilometer" << endl;
                cout << "Rute: ";
                printPath(previous, start, end);
            }
            else
            {
                cout << "Tidak ada jalur dari " << start << " ke " << end << endl;
            }
        }
        else if (pilihan == 2)
        {
            cout << border << endl;
            infoBarang info;
            TreeNode *root = nullptr;
            queue<tuple<string, string, string>> tempQueue;

            // string lokasi, tujuan, berkas;
            char pilihan;

            // Loop input
            do
            {
                cout << "Masukkan berkas: ";
                cin.ignore();
                getline(cin, info.berkas);
                // cin >> berkas;
                cout << "Masukkan lokasi: ";
                getline(cin, info.lokasi);
                // cin >> lokasi;
                cout << "Masukkan tujuan: ";
                getline(cin, info.tujuan);
                // cin >> tujuan;

                inputQueue.push(make_tuple(info.lokasi, info.tujuan, info.berkas));
                tempQueue.push(make_tuple(info.lokasi, info.tujuan, info.berkas));

                cout << "Apakah Anda ingin memasukkan berkas lain? (y/n): ";
                cin >> pilihan;
            } while (pilihan == 'y' || pilihan == 'Y');

            // Memproses queue dan membangun BST
            while (!tempQueue.empty())
            {
                auto entry = tempQueue.front();
                tempQueue.pop();
                root = masukkanBerkas(root, get<0>(entry), get<1>(entry), get<2>(entry));
                }

            // Menampilkan berkas yang dikelompokkan berdasarkan lokasi
            cout << "\nBerkas yang dikelompokkan berdasarkan lokasi dan tujuan:\n";
            cout << "=====================================\n";
            inorderTraversal(root);
            cout << "=====================================\n";
        }
        else if (pilihan == 3)
        {
            cout << border << endl;
            inisialisasiGraf(9);

            tambahEdge(0, 1, 4);
            tambahEdge(0, 7, 8);
            tambahEdge(1, 2, 8);
            tambahEdge(1, 7, 11);
            tambahEdge(2, 3, 7);
            tambahEdge(2, 8, 2);
            tambahEdge(2, 5, 4);
            tambahEdge(3, 4, 9);
            tambahEdge(3, 5, 14);
            tambahEdge(4, 5, 10);
            tambahEdge(5, 6, 2);
            tambahEdge(6, 7, 1);
            tambahEdge(6, 8, 6);
            tambahEdge(7, 8, 7);

            int sumber = 0;
            int tujuan = 4;
            int waktuBerlalu = 10; // Waktu yang telah berlalu

            int lokasiSaatIni = lacakBarang(sumber, tujuan, waktuBerlalu);

            if (lokasiSaatIni != -1)
            {
                cout << "Barang saat ini berada di lokasi: " << lokasiSaatIni << endl;
            }
        }
        else if (pilihan == 4)
        {
            cout << border << endl;
            // Membuat node untuk setiap lokasi
            Node *cibiru = createNode("UPI Cibiru", 0);
            Node *bumsil = createNode("UPI BUMSIL", 30); // waktu tempuh 30 menit dari UPI Cibiru ke UPI BUMSIL

            // Tempat di UPI BUMSIL
            Node *rektorat = createNode("Gedung Rektorat", 10);
            Node *akmawa = createNode("Akademik Mahasiswa", 5);
            Node *sdti = createNode("SDTI", 8);
            Node *keuangan = createNode("Direktorat Keuangan", 7);
            Node *ahsun = createNode("Gedung Ahmad Sanusi", 12);

            // Membuat struktur tree
            tambahAnak(cibiru, bumsil);
            tambahAnak(bumsil, rektorat);
            tambahAnak(bumsil, akmawa);
            tambahAnak(bumsil, sdti);
            tambahAnak(bumsil, keuangan);
            tambahAnak(bumsil, ahsun);

            // Menampilkan estimasi waktu dari UPI Cibiru
            cout << "Estimasi waktu pengiriman dari UPI Cibiru:" << endl;
            int counter = 1;
            estimasi(bumsil, 0, counter);
        }
        else if (pilihan == 5)
        {
            cout << border << endl;
            info informasi;

            // Input informasi pengirim
            cout << endl;
            cout << "Masukkan informasi pengirim" << endl;
            cout << endl;
            cout << border << endl;
            cout << "Nama Lengkap: ";
            cin.ignore();
            getline(cin, informasi.namaPengirim);
            cout << border << endl;
            cout << "Alamat: ";
            cin.ignore();
            getline(cin, informasi.alamatPengirim);
            cout << border << endl;
            cout << "Nomor Handphone: ";
            cin.ignore();
            getline(cin, informasi.kontakPengirim);
            cout << border << endl;

            // Input informasi penerima
            cout << endl;
            cout << "Masukkan informasi penerima" << endl;
            cout << endl;
            cout << border << endl;
            cout << "Nama Lengkap: ";
            getline(cin, informasi.namaPenerima);
            cout << border << endl;
            cout << "Alamat: ";
            getline(cin, informasi.alamatPenerima);
            cout << border << endl;
            cout << "Nomor Handphone: ";
            getline(cin, informasi.kontakPenerima);
            cout << border << endl;
            cout << "Masukkan nomor resi: ";
            cin >> informasi.nomorResi;
            cout << border << endl;

            // Input tgl kirim
            cout << "Masukkan tanggal pengiriman (dd/mm/yyyy): ";
            cin >> informasi.tglKirim;

            // Input berat barang
            cout << "Masukkan berat barang (dalam gram): ";
            cin >> informasi.beratBarang;

            // Menampilkan resi barang
            cout << "\n=== Resi Barang ===" << endl;
            cout << "Informasi Pengirim:" << endl;
            cout << "Nama Lengkap: " << informasi.namaPengirim << endl;
            cout << "Alamat: " << informasi.alamatPengirim << endl;
            cout << "Nomor Handphone: " << informasi.kontakPengirim << endl;

            cout << "\nInformasi Penerima:" << endl;
            cout << "Nama Lengkap: " << informasi.namaPenerima << endl;
            cout << "Alamat: " << informasi.alamatPenerima << endl;
            cout << "Nomor Handphone: " << informasi.kontakPenerima << endl;

            cout << "\nNomor Resi: " << informasi.nomorResi << endl;
            cout << "Tanggal Pengiriman: " << informasi.tglKirim << endl;
            cout << "Berat Barang: " << informasi.beratBarang << " gram" << endl;
        }
        else if (pilihan == 6)
        {
            cout << border << endl;
            cout << "\nDaftar Antrian Berkas: "<< endl;
            displayQueue(inputQueue); // menampilkan seluruh antrian
        }
    } while (pilihan != 7);
    cout << "Terimakasih Sudah Menggunakan Aplikasi Kami :)";

    return 0;
}