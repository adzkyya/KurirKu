#include <iostream>
#include <queue>
using namespace std;

const int ukuran = 20;
struct Barang {
    int top; 
    string isi[ukuran]; 
    int total[ukuran]; 
    string nama; // input nama barang 
    int jumlah; // input jumlah barang
} q;

void createQueue(){
    q.top = 0;
}

void displayQueue(){
        cout << "\n====== Menampilkan Daftar Antrian ======"<< endl;
        cout << "No |   Nama Barang   |   Jumlah Barang   |" << endl;
        for (int i = 0; i < q.top; i++)
        {
            cout << i+1 << "  |  " << q.isi[i] << "   |   " << q.total[i] << "   |" << endl;
        }
    
}
void insertQueue(string namaBarang, int jumlahBarang){
        q.isi[q.top] = namaBarang;
        q.total[q.top] = jumlahBarang;
        q.top++;
}

int main() {
    queue<Barang> antrianBarang;
    int banyakBarang;
    char daftarAntrian;

    // input data barang
    cout << "Banyak barang yang akan ditambahkan: ";
    cin >> banyakBarang;
    system("cls");
    createQueue(); //membuat antrian
    for (int i = 0; i < banyakBarang; i++) {
        Barang barang;
        cout << "\nMasukkan nama barang ke-" << i+1 << ": ";
        cin.ignore();
        getline(cin, barang.nama);
        cout << "Masukkan jumlah barang: ";
        cin >> barang.jumlah;
        //memasukkan barang ke antrian
        insertQueue(barang.nama,barang.jumlah);
        cout << "Barang berhasil ditambahkan dalam antrian." << endl;
        
    }

    cout << "\nTampilkan daftar antrian? (y/n): ";
    cin >> daftarAntrian;
    if (daftarAntrian == 'y')
    {
        displayQueue(); //menampilkan seluruh antrian
    } else {
        cout << "Antrian tidak ditampilkan.";
    }
    
return 0;
}