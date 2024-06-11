#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <climits>
#include <fstream>
#include <limits.h>
#include <cstring>
#include <conio.h>

using namespace std;
string borderKecil = "------------------------------------------";
string border = "============================================";
string welcome = "SELAMAT DATANG DI APLIKASI UPI FILE EXPRESS";

// Login Register
struct UserData
{
    string username, password;
    double saldo;
};

void registerUser()
{
    string username, password;
    cout << "Masukkan username: ";
    cin >> username;

    cout << "Masukkan password: ";
    char ch;
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b')
        {
            if (password.length() > 0)
            {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else
        {
            cout << '*';
            password += ch;
        }
    }

    ofstream file("users.txt", ios::app);
    if (file.is_open())
    {
        file << username << " " << password << endl;
        file.close();
        cout << endl
             << "Registrasi berhasil" << endl;
    }
    else
    {
        cout << endl
             << "Gagal membuka file" << endl;
    }
}

bool loginUser()
{
    string username, password;
    cout << "Masukkan username: ";
    cin >> username;

    cout << "Masukkan password: ";
    char ch;
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b')
        {
            if (password.length() > 0)
            {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else
        {
            cout << '*';
            password += ch;
        }
    }

    ifstream file("users.txt");
    if (file.is_open())
    {
        string storedUsername, storedPassword;
        while (file >> storedUsername >> storedPassword)
        {
            if (storedUsername == username && storedPassword == password)
            {
                file.close();
                cout << endl
                     << "Login berhasil" << endl;
                return true;
            }
        }
        file.close();
    }
    else
    {
        cout << endl
             << "Gagal membuka file" << endl;
    }

    cout << "Username atau password salah" << endl;
    return false;
}

// Fitur Nomer 1: Struktur untuk menyimpan informasi graf
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
    for (const auto &pair : graph.adjList)
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

// Fitur nomer 2: Struktur untuk mengelompokkan barang berdasarkan lokasi dan tujuan
struct infoBarang
{
    string lokasi;
    string tujuan;
    string berkas;
    string date;
};

struct TreeNode
{
    string lokasi; // Add the 'lokasi' member
    string tujuan; // Add the 'tujuan' member
    infoBarang info;
    queue<string> berkas;
    TreeNode *kiri;
    TreeNode *kanan;

    // Constructor to initialize the infoBarang part of TreeNode
    TreeNode(string loc, string dest, string berk) : lokasi(loc), tujuan(dest), info{loc, dest, berk}, kiri(nullptr), kanan(nullptr) {}
    TreeNode(string loc, string dest) : lokasi(loc), tujuan(dest), info{loc, dest, ""}, kiri(nullptr), kanan(nullptr) {}
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
        cout << borderKecil << endl;
        cout << "Kampus: " << root->lokasi << endl;
        cout << "Gedung: " << root->tujuan << endl;
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

// Fitur nomer 3: Fungsi untuk menghitung lokasi barang berdasarkan waktu dan kecepatan
void hitungLokasiBarang(double jam, double kilometer)
{
    double jarakTempuh = kilometer;

    if (kilometer <= jarakTempuh)
    {
        cout << "Barang saat ini sudah mencapai tujuan." << endl;
    }
    else
    {
        cout << "Barang masih dalam perjalanan.\n";
        // cout << "Perkiraan kilometer yang sudah ditempuh: " << jarakTempuh << " km\n";
        // cout << "Total kilometer yang harus ditempuh: " << kilometer << " km\n";
    }
}

// Fitur nomer 4: Fungsi untuk estimasi waktu pengiriman berdasarkan jarak terpendek dan kecepatan rata-rata
void estimasiWaktuSampai(const Graph &graph, const string &start, const string &end, double kecepatanRataRata)
{
    unordered_map<string, string> previous;
    unordered_map<string, int> distances = dijkstra(graph, start, previous);

    if (distances[end] != INT_MAX)
    {
        double waktu = distances[end] / kecepatanRataRata;
        cout << "Estimasi waktu sampai dari " << start << " ke " << end << " adalah " << waktu << " jam." << endl;
        cout << "Rute: ";
        printPath(previous, start, end);
    }
    else
    {
        cout << "Tidak ada jalur yang menghubungkan " << start << " dan " << end << endl;
    }
}

// Fitur nomer 5: Struktur untuk menyimpan informasi pengirim dan penerima
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
    double beratBarang;
};

void resi()
{
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

// Fitur nomer 7

void displayQueue(const queue<tuple<string, string, string, string>>& inputQueue) {
    if (inputQueue.empty()) {
        cout << "Tidak Terdapat Antrian Berkas" << endl;
        return;
        }

cout << "| No |   Nama Berkas   |   Tujuan   |   Lokasi   |   Tanggal Pengiriman   |" << endl;

    queue<tuple<string, string, string, string>> tempQueue(inputQueue);
    int queueSize = tempQueue.size();
    
    while (!tempQueue.empty()) {
        string location, destination, file, date;
        tie(location, destination, file, date) = tempQueue.front(); 
        tempQueue.pop();
        for (int i = 0; i < queueSize; i++)
        {
            cout <<"| " << i+1 << " | " << file << " | " <<  destination << " | " << location << " | " << date << " | " << endl;
        }
        break;
    }
}

int main()
{
    // fitur upi file express
    // 1. register
    // 2. ⁠login
    // 3. ⁠pengelompokkan barang berdasarkan lokasi
    // 4. ⁠pelacakan barang
    // 5. ⁠estimasi waktu sampai
    // 6. ⁠resi barang
    // 7. pengelolaan antrian pengiriman
    int pilihan;
    bool isLoggedIn = false;
    queue<tuple<string, string, string, string>> inputQueue;
    int queueSize = 0;
    
    do
    {
        cout << border << "\n"
             << welcome << "\n"
             << border << endl;
        cout << "1. Register\n2. Login\n3. Pengelompokkan Barang Berdasarkan Lokasi\n4. Pelacakan Barang\n5. Estimasi Waktu Sampai\n6. Resi Barang\n7. Pengelolaan Antrian Pengiriman\n8. Exit\n"
             << border << "\nMasukkan Pilihan Anda: ";
        cin >> pilihan;

        cout << border << endl;
        if (pilihan == 1)
        {
            registerUser();
        }
        else if (pilihan == 2)
        {
            if (loginUser())
            {
                isLoggedIn = true;
                cout << "Login berhasil" << endl;
            }
        }
        else if (pilihan == 3)
        {
            cout << border << endl;
            if (isLoggedIn)
            {
                infoBarang info;
                TreeNode *root = nullptr;
                queue<tuple<string, string, string, string>> tempQueue;
                int jumlahBarang;
                cout << "Masukkan jumlah barang: ";
                cin >> jumlahBarang;
                jumlahBarang == queueSize;

                for (int i = 0; i < jumlahBarang; ++i)
                {
                    string lokasi, tujuan, berkas;
                    cout << "Masukkan kampus tujuan: ";
                    cin.ignore();
                    getline(cin, info.lokasi);
                    // cin >> lokasi;
                    cout << "Masukkan gedung tujuan: ";
                    getline(cin, info.tujuan);
                    // cin >> tujuan;
                    cout << "Masukkan nama berkas: ";
                    getline(cin, info.berkas);
                    cout << endl;
                    cout << borderKecil << endl;
                    // cin >> berkas;
                    root = masukkanBerkas(root, info.lokasi, info.tujuan, info.berkas);
                    inputQueue.push(make_tuple(info.lokasi, info.tujuan, info.berkas, info.date));
                    tempQueue.push(make_tuple(info.lokasi, info.tujuan, info.berkas, info.date));

                }

                cout << "Barang yang dikelompokkan berdasarkan kampus dan gedung:" << endl;
                inorderTraversal(root);
            }
            else
            {
                cout << "Anda harus login terlebih dahulu" << endl;
            }
        }
        else if (pilihan == 4)
        {
            cout << border << endl;
            if (isLoggedIn)
            {
                double jam, kilometer, kecepatanRataRata;
                cout << "Perkiraan waktu tempuh dalam jam: ";
                cin >> jam;
                cout << "Masukkan jarak tempuh dalam kilometer: ";
                cin >> kilometer;

                hitungLokasiBarang(jam, kilometer);
            }
            else
            {
                cout << "Anda harus login terlebih dahulu" << endl;
            }
        }
        else if (pilihan == 5)
        {
            cout << border << endl;
            if (isLoggedIn)
            {
                Graph graph;
                int numEdges;
                cout << "Masukkan jumlah edge: ";
                cin >> numEdges;

                cout << "Masukkan edge dalam format: tempat_awal tempat_tujuan bobot" << endl;
                for (int i = 0; i < numEdges; ++i)
                {
                    string u, v;
                    int weight;
                    cin >> u >> v >> weight;
                    addEdge(graph, u, v, weight);
                }

                string start, end;
                double kecepatanRataRata;
                cout << "Masukkan tempat awal: ";
                cin >> start;
                cout << "Masukkan tempat tujuan: ";
                cin >> end;
                cout << "Masukkan kecepatan rata-rata dalam km/jam: ";
                cin >> kecepatanRataRata;

                estimasiWaktuSampai(graph, start, end, kecepatanRataRata);
            }
            else
            {
                cout << "Anda harus login terlebih dahulu" << endl;
            }
        }
        else if (pilihan == 6)
        {
            cout << border << endl;
            if (isLoggedIn)
            {
                resi();
            }
            else
            {
                cout << "Anda harus login terlebih dahulu" << endl;
            }
        }
        else if (pilihan == 7)
        {
            cout << border << endl;
            if (isLoggedIn)
            {
                cout << border << endl;
                cout << "\nDaftar Antrian Berkas " << endl;
                displayQueue(inputQueue); // menampilkan seluruh antrian
            }
            else
            {
                cout << "Anda harus login terlebih dahulu" << endl;
            }
        }
    } while (pilihan != 8);

    return 0;
}