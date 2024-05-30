#include <iostream>
#include <queue>
#include <string>

using namespace std;

//fitur untuk mengelompokkan barang berdasarkan lokasi dan tujuan
struct TreeNode {
    string lokasi;
    string tujuan;
    queue<string> berkas;
    TreeNode* kiri;
    TreeNode* kanan;
    
    TreeNode(string loc, string dest) : lokasi(loc), tujuan(dest), kiri(nullptr), kanan(nullptr) {}
};

// Fungsi untuk memasukkan berkas baru ke dalam BST
TreeNode* masukkanBerkas(TreeNode* root, const string& lokasi, const string& tujuan, const string& berkas) {
    if (root == nullptr) {
        root = new TreeNode(lokasi, tujuan);
        root->berkas.push(berkas);
    } else if (lokasi < root->lokasi || (lokasi == root->lokasi && tujuan < root->tujuan)) {
        root->kiri = masukkanBerkas(root->kiri, lokasi, tujuan, berkas);
    } else if (lokasi > root->lokasi || (lokasi == root->lokasi && tujuan > root->tujuan)) {
        root->kanan = masukkanBerkas(root->kanan, lokasi, tujuan, berkas);
    } else {
        root->berkas.push(berkas);
    }
    
    return root;
}

// Fungsi untuk melakukan traversal in-order pada BST dan mencetak berkas yang dikelompokkan berdasarkan lokasi
void inorderTraversal(TreeNode* root) {
    if (root != nullptr) {
        inorderTraversal(root->kiri);
        cout << "-------------------------------------" << endl;
        cout << "Lokasi: " << root->lokasi << endl;
        cout << "Tujuan: " << root->tujuan << endl;
        cout << "Berkas: ";
        queue<string> tempQueue = root->berkas;
        while (!tempQueue.empty()) {
            cout << tempQueue.front() << " ";
            tempQueue.pop();
        }
        cout << endl;
        inorderTraversal(root->kanan);
    }
}

int main() {
    TreeNode* root = nullptr;
    queue<tuple<string, string, string>> inputQueue;
    
    string lokasi, tujuan, berkas;
    char pilihan;
    
    // Loop input
    do {
        cout << "Masukkan berkas: ";
        cin >> berkas;
        cout << "Masukkan lokasi: ";
        cin >> lokasi;
        cout << "Masukkan tujuan: ";
        cin >> tujuan;
        
        inputQueue.push(make_tuple(lokasi, tujuan, berkas));
        
        cout << "Apakah Anda ingin memasukkan berkas lain? (y/n): ";
        cin >> pilihan;
    } while (pilihan == 'y' || pilihan == 'Y');
    
    // Memproses queue dan membangun BST
    while (!inputQueue.empty()) {
        auto entry = inputQueue.front();
        inputQueue.pop();
        root = masukkanBerkas(root, get<0>(entry), get<1>(entry), get<2>(entry));
    }
    
    // Menampilkan berkas yang dikelompokkan berdasarkan lokasi
    cout << "\nBerkas yang dikelompokkan berdasarkan lokasi dan tujuan:\n";
    cout << "=====================================\n";
    inorderTraversal(root);
    cout << "=====================================\n";
    
    return 0;
}
