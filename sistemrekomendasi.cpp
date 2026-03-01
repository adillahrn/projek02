#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <algorithm>
using namespace std;

// --- Struct dasar transaksi ---
struct Transaction {
    int transactionID;
    int customerID;
    int productID;
    string productName;
    string category;
    int quantity;
    string date;
};

// --- Global data ---
vector<Transaction> transactions; // menyimpan semua transaksi
unordered_map<int, vector<Transaction>> customerMap; // mapping customerID -> list transaksi
unordered_map<int, int> productFrequency; // mapping productID -> total quantity

// --- Fungsi bantu ---
Transaction createTransaction(int tid, int cid, int pid, string pname, string cat, int qty, string date) {
    return Transaction{tid, cid, pid, pname, cat, qty, date};
}

// --- Insert transaksi ---
void insertTransaction(Transaction t) {
    transactions.push_back(t);                  // simpan di array
    customerMap[t.customerID].push_back(t);    // simpan di map per customer
    productFrequency[t.productID] += t.quantity; // update frekuensi produk
    cout << "Transaksi berhasil ditambahkan.\n";
}

// --- Search riwayat transaksi berdasarkan customer ---
void searchByCustomer(int customerID) {
    if(customerMap.find(customerID) != customerMap.end()) {
        cout << "Riwayat transaksi Customer " << customerID << ":\n";
        for(auto &t : customerMap[customerID]) {
            cout << "ID Transaksi: " << t.transactionID
                 << " | Produk: " << t.productName
                 << " | Qty: " << t.quantity
                 << " | Tanggal: " << t.date << "\n";
        }
    } else {
        cout << "Customer tidak ditemukan.\n";
    }
}

// --- Update transaksi berdasarkan transactionID ---
bool updateTransaction(int transactionID, Transaction newT) {
    for(auto &t : transactions) {
        if(t.transactionID == transactionID) {
            productFrequency[t.productID] -= t.quantity;
            t = newT;
            productFrequency[t.productID] += t.quantity;
            // update di map customer
            auto &vec = customerMap[newT.customerID];
            for(auto &c : vec){
                if(c.transactionID == transactionID) {
                    c = newT;
                    break;
                }
            }
            return true;
        }
    }
    return false;
}

// --- Delete transaksi berdasarkan transactionID ---
bool deleteTransaction(int transactionID) {
    for(size_t i=0; i<transactions.size(); i++) {
        if(transactions[i].transactionID == transactionID) {
            productFrequency[transactions[i].productID] -= transactions[i].quantity;
            // hapus dari map customer
            auto &vec = customerMap[transactions[i].customerID];
            vec.erase(remove_if(vec.begin(), vec.end(),
                        [transactionID](Transaction &t){ return t.transactionID == transactionID; }),
                        vec.end());
            transactions.erase(transactions.begin() + i);
            return true;
        }
    }
    return false;
}

// --- Generate Top-N produk terlaris ---
void topNProducts(int N) {
    vector<pair<int,int>> freqVec(productFrequency.begin(), productFrequency.end());
    sort(freqVec.begin(), freqVec.end(), [](pair<int,int> a, pair<int,int> b){
        return b.second > a.second; // descending
    });
    cout << "Top-" << N << " Produk Terlaris:\n";
    for(int i=0; i<min(N,(int)freqVec.size()); i++) {
        cout << "Product ID: " << freqVec[i].first << " | Terjual: " << freqVec[i].second << "\n";
    }
}

// --- Simpan ke file CSV ---
void saveToFile(const string &filename) {
    ofstream fout(filename);
    fout << "TransactionID,CustomerID,ProductID,ProductName,Category,Quantity,Date\n";
    for(auto &t : transactions) {
        fout << t.transactionID << "," << t.customerID << "," << t.productID << "," 
             << t.productName << "," << t.category << "," << t.quantity << "," << t.date << "\n";
    }
    fout.close();
    cout << "Data berhasil disimpan ke " << filename << endl;
}

// --- Load dari file CSV ---
void loadFromFile(const string &filename) {
    ifstream fin(filename);
    if(!fin) { cout << "File tidak ditemukan!\n"; return; }
    transactions.clear();
    customerMap.clear();
    productFrequency.clear();

    string line;
    getline(fin, line); // skip header
    while(getline(fin, line)) {
        int tid, cid, pid, qty;
        string pname, cat, date;
        size_t pos = 0;
        vector<string> tokens;
        string token;
        while((pos = line.find(',')) != string::npos) {
            token = line.substr(0,pos);
            tokens.push_back(token);
            line.erase(0,pos+1);
        }
        tokens.push_back(line); // last token
        tid = stoi(tokens[0]);
        cid = stoi(tokens[1]);
        pid = stoi(tokens[2]);
        pname = tokens[3];
        cat = tokens[4];
        qty = stoi(tokens[5]);
        date = tokens[6];
        Transaction t = createTransaction(tid,cid,pid,pname,cat,qty,date);
        insertTransaction(t);
    }
    fin.close();
    cout << "Data berhasil dimuat dari " << filename << endl;
}

// --- Menu interaktif ---
void menu() {
    int choice;
    do {
        cout << "\n=== Sistem Rekomendasi Produk ===\n";
        cout << "1. Insert Transaksi\n2. Search by Customer\n3. Update Transaksi\n4. Delete Transaksi\n5. Top-N Produk\n6. Save ke File\n7. Load dari File\n0. Exit\nPilihan: ";
        cin >> choice;
        if(choice==1){
            int tid, cid, pid, qty;
            string pname, cat, date;
            cout << "TransactionID CustomerID ProductID ProductName Category Quantity Date (pisahkan spasi): ";
            cin >> tid >> cid >> pid;
            cin.ignore(); // agar getline tidak terlewat
            getline(cin, pname);
            getline(cin, cat);
            cin >> qty;
            cin.ignore();
            getline(cin, date);
            insertTransaction(createTransaction(tid,cid,pid,pname,cat,qty,date));
        }
        else if(choice==2){
            int cid; cout << "CustomerID: "; cin >> cid;
            searchByCustomer(cid);
        }
        else if(choice==3){
            int tid, cid, pid, qty;
            string pname, cat, date;
            cout << "TransactionID to update: "; cin >> tid;
            cout << "New CustomerID ProductID ProductName Category Quantity Date (pisahkan spasi): ";
            cin >> cid >> pid; cin.ignore();
            getline(cin, pname); getline(cin, cat);
            cin >> qty; cin.ignore();
            getline(cin, date);
            if(updateTransaction(tid, createTransaction(tid,cid,pid,pname,cat,qty,date)))
                cout << "Update sukses\n";
            else cout << "Transaksi tidak ditemukan\n";
        }
        else if(choice==4){
            int tid; cout << "TransactionID to delete: "; cin >> tid;
            if(deleteTransaction(tid)) cout << "Delete sukses\n";
            else cout << "Transaksi tidak ditemukan\n";
        }
        else if(choice==5){
            int N; cout << "Top-N: "; cin >> N;
            topNProducts(N);
        }
        else if(choice==6){
            string filename; cout << "Filename: "; cin >> filename;
            saveToFile(filename);
        }
        else if(choice==7){
            string filename; cout << "Filename: "; cin >> filename;
            loadFromFile(filename);
        }
    } while(choice != 0);
}

int main() {
    menu();
    return 0;
}