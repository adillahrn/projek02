#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;

struct Transaction {
    string transaction_id;
    string customer_id;
    string product_id;
    string product_name;
    string category;
    int quantity;
    string order_date;
};

vector<Transaction> transactions;

long long lastInsertTime = 0;
long long lastSearchTime = 0;
long long lastUpdateTime = 0;
long long lastDeleteTime = 0;
long long lastShowTime   = 0;

string trim(string s) {
    while (!s.empty() && isspace(s.front())) s.erase(0,1);
    while (!s.empty() && isspace(s.back())) s.pop_back();
    return s;
}

chrono::high_resolution_clock::time_point startTimer() {
    return chrono::high_resolution_clock::now();
}

long long stopTimer(chrono::high_resolution_clock::time_point start) {
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

int loadCSV(string filename) {

    ifstream file(filename);
    if (!file.is_open()) return 0;

    string line;
    getline(file,line);

    while(getline(file,line)) {

        stringstream ss(line);
        string token;

        Transaction t;

        getline(ss,t.transaction_id,',');
        getline(ss,t.customer_id,',');
        getline(ss,t.product_id,',');
        getline(ss,t.product_name,',');
        getline(ss,t.category,',');
        getline(ss,token,',');
        t.quantity = stoi(token);
        getline(ss,t.order_date,',');

        transactions.push_back(t);
    }

    file.close();
    return transactions.size();
}

void tampilSemuaTransaksi() {

    cout << "\nDATA TRANSAKSI\n\n";

    for (auto &t : transactions) {

        cout << t.transaction_id << " | "
             << t.customer_id << " | "
             << t.product_id << " | "
             << t.product_name << " | "
             << t.category << " | "
             << t.quantity << " | "
             << t.order_date << endl;
    }
}

void insertTransaction(Transaction t) {
    transactions.push_back(t);
}

vector<Transaction> searchByTransactionId(string id) {

    vector<Transaction> hasil;

    for(auto &t : transactions) {
        if(t.transaction_id == id)
            hasil.push_back(t);
    }

    return hasil;
}

vector<Transaction> searchByCustomerId(string id) {

    vector<Transaction> hasil;

    for(auto &t : transactions) {
        if(t.customer_id == id)
            hasil.push_back(t);
    }

    return hasil;
}

vector<Transaction> searchByProductId(string id) {

    vector<Transaction> hasil;

    for(auto &t : transactions) {
        if(t.product_id == id)
            hasil.push_back(t);
    }

    return hasil;
}

bool updateByTransactionId(string id, Transaction newData) {

    for(auto &t : transactions) {

        if(t.transaction_id == id) {

            t = newData;
            return true;
        }
    }

    return false;
}

bool deleteByTransactionId(string id) {

    for(int i=0;i<transactions.size();i++) {

        if(transactions[i].transaction_id == id) {

            transactions.erase(transactions.begin()+i);
            return true;
        }
    }

    return false;
}

void printMenu() {

    cout << "\n=== SISTEM REKOMENDASI PRODUK ===\n";
    cout << "1. Tampilkan Semua Transaksi\n";
    cout << "2. Insert Transaksi\n";
    cout << "3. Search Transaction ID\n";
    cout << "4. Search Customer ID\n";
    cout << "5. Search Product ID\n";
    cout << "6. Update Transaksi\n";
    cout << "7. Delete Transaksi\n";
    cout << "8. Statistik Eksekusi\n";
    cout << "0. Keluar\n";
    cout << "Pilih: ";
}

int main() {

    cout << "Loading transactions.csv...\n";

    auto t0 = startTimer();
    int loaded = loadCSV("trans20k.csv");
    long long loadTime = stopTimer(t0);

    if(loaded==0) {
        cout << "File tidak ditemukan\n";
        return 0;
    }

    cout << "Data Loaded : " << loaded << endl;
    cout << "Load Time   : " << loadTime << " ms\n";

    int pilih;

    do {

        printMenu();
        cin >> pilih;
        cin.ignore();

        switch(pilih) {

        case 1: {

            auto t = startTimer();
            tampilSemuaTransaksi();
            lastShowTime = stopTimer(t);

            cout << "waktu = " << lastShowTime << " ms\n";
            break;
        }

        case 2: {

            Transaction t;

            cout << "Transaction ID : "; getline(cin,t.transaction_id);
            cout << "Customer ID    : "; getline(cin,t.customer_id);
            cout << "Product ID     : "; getline(cin,t.product_id);
            cout << "Product Name   : "; getline(cin,t.product_name);
            cout << "Category       : "; getline(cin,t.category);

            cout << "Quantity       : ";
            string qty;
            getline(cin,qty);
            t.quantity = stoi(qty);

            cout << "Order Date     : ";
            getline(cin,t.order_date);

            auto ts = startTimer();
            insertTransaction(t);
            lastInsertTime = stopTimer(ts);

            cout << "Insert berhasil\n";
            cout << "waktu = " << lastInsertTime << " ms\n";

            break;
        }

        case 3: {

            string id;
            cout << "Transaction ID : ";
            getline(cin,id);

            auto t = startTimer();
            auto hasil = searchByTransactionId(id);
            lastSearchTime = stopTimer(t);

            cout << "Ditemukan " << hasil.size() << " transaksi\n";
            cout << "waktu = " << lastSearchTime << " ms\n";

            break;
        }

        case 4: {

            string id;
            cout << "Customer ID : ";
            getline(cin,id);

            auto t = startTimer();
            auto hasil = searchByCustomerId(id);
            lastSearchTime = stopTimer(t);

            cout << "Ditemukan " << hasil.size() << " transaksi\n";
            cout << "waktu = " << lastSearchTime << " ms\n";

            break;
        }

        case 5: {

            string id;
            cout << "Product ID : ";
            getline(cin,id);

            auto t = startTimer();
            auto hasil = searchByProductId(id);
            lastSearchTime = stopTimer(t);

            cout << "Ditemukan " << hasil.size() << " transaksi\n";
            cout << "waktu = " << lastSearchTime << " ms\n";

            break;
        }

        case 6: {

            string id;
            cout << "Transaction ID yang diupdate: ";
            getline(cin,id);

            Transaction t;

            cout << "Product Name Baru : ";
            getline(cin,t.product_name);

            auto ts = startTimer();
            bool ok = updateByTransactionId(id,t);
            lastUpdateTime = stopTimer(ts);

            if(ok) cout << "Update berhasil\n";
            else cout << "Data tidak ditemukan\n";

            cout << "waktu = " << lastUpdateTime << " ms\n";

            break;
        }

        case 7: {

            string id;
            cout << "Transaction ID yang dihapus: ";
            getline(cin,id);

            auto ts = startTimer();
            bool ok = deleteByTransactionId(id);
            lastDeleteTime = stopTimer(ts);

            if(ok) cout << "Delete berhasil\n";
            else cout << "Data tidak ditemukan\n";

            cout << "waktu = " << lastDeleteTime << " ms\n";

            break;
        }

        case 8: {

            cout << "\nStatistik Eksekusi (ms)\n";
            cout << "Insert : " << lastInsertTime << endl;
            cout << "Search : " << lastSearchTime << endl;
            cout << "Update : " << lastUpdateTime << endl;
            cout << "Delete : " << lastDeleteTime << endl;
            cout << "Show   : " << lastShowTime   << endl;

            break;
        }

        }

    } while(pilih!=0);

}