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

vector<Transaction> loadCSV(string filename){

    vector<Transaction> data;
    ifstream file(filename);
    string line;

    getline(file,line); // skip header

    while(getline(file,line)){

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

        getline(ss,t.order_date);

        data.push_back(t);
    }

    file.close();
    return data;
}

void benchmark(string filename){

    vector<Transaction> transactions = loadCSV(filename);
    int n = transactions.size();

    cout << "\nTotal Data : " << n << endl;

    Transaction newT;
    newT.transaction_id="NEWID";
    newT.customer_id="CUSTX";
    newT.product_id="PRODX";
    newT.product_name="NewProduct";
    newT.category="Test";
    newT.quantity=1;
    newT.order_date="2026-01-01";

    /* INSERT */

    auto start = chrono::high_resolution_clock::now();

    for(int i=0;i<n;i++){
        transactions.push_back(newT);
    }

    auto end = chrono::high_resolution_clock::now();

    double insertTime =
    chrono::duration<double,milli>(end-start).count();


    /* SEARCH */

    string target = transactions[n-1].transaction_id;

    start = chrono::high_resolution_clock::now();

    for(int i=0;i<n;i++){
        if(transactions[i].transaction_id == target){
            break;
        }
    }

    end = chrono::high_resolution_clock::now();

    double searchTime =
    chrono::duration<double,milli>(end-start).count();


    /* UPDATE */

    start = chrono::high_resolution_clock::now();

    for(int i=0;i<n;i++){
        if(transactions[i].transaction_id == target){
            transactions[i].product_name="UPDATED";
        }
    }

    end = chrono::high_resolution_clock::now();

    double updateTime =
    chrono::duration<double,milli>(end-start).count();


    /* DELETE */

    start = chrono::high_resolution_clock::now();

    for(int i=0;i<n/2;i++){
        transactions.pop_back();
    }

    end = chrono::high_resolution_clock::now();

    double deleteTime =
    chrono::duration<double,milli>(end-start).count();


    /* SHOW (ITERATE ALL DATA) */

    start = chrono::high_resolution_clock::now();

    for(auto &t : transactions){
        volatile string x = t.product_name;
    }

    end = chrono::high_resolution_clock::now();

    double showTime =
    chrono::duration<double,milli>(end-start).count();


    cout << "\nExecution Time Statistics (ms)\n";

    cout << "Insert Time : " << insertTime << endl;
    cout << "Search Time : " << searchTime << endl;
    cout << "Update Time : " << updateTime << endl;
    cout << "Delete Time : " << deleteTime << endl;
    cout << "Show Time   : " << showTime << endl;

}

int main(){

    benchmark("trans1000.csv");
    benchmark("trans10000.csv");
    benchmark("trans20000.csv");

    return 0;
}