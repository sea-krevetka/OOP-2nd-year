#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class TeaPurchase {
public:
    string tea_type;
    string package_type;
    string producer;
    double price;
    int quantity;
    double total_sum;

    TeaPurchase() {
        price = 0;
        quantity = 0;
        total_sum = 0;
    }
    
    void readFromFile(ifstream& inFile) {
        size_t size;

        inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
        tea_type.resize(size);
        inFile.read(&tea_type[0], size);

        inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
        package_type.resize(size);
        inFile.read(&package_type[0], size);

        inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
        producer.resize(size);
        inFile.read(&producer[0], size);

        inFile.read(reinterpret_cast<char*>(&price), sizeof(price));
        inFile.read(reinterpret_cast<char*>(&quantity), sizeof(quantity));
        inFile.read(reinterpret_cast<char*>(&total_sum), sizeof(total_sum));
    }
    
    void print() const {
        cout << left << setw(25) << tea_type 
             << left << setw(20) << package_type 
             << left << setw(20) << producer 
             << left << setw(10) << price 
             << left << setw(12) << quantity 
             << left << setw(15) << total_sum << endl;
    }
    static void printHeader() {
        cout << left << setw(25) << "Tea type" 
            << left << setw(20) << "Package type" 
            << left << setw(20) << "Producer"
            << left << setw(10) << "Price" 
            << left << setw(12) << "Amount" 
            << left << setw(15) << "Summ" << endl;

        cout << string(92, '-') << endl;
    }

    static void printFooter(double grand_total) {
        cout << string(92, '-') << endl;
        cout << left << setw(55) << "Всего:" 
             << right << setw(37) << fixed << setprecision(2) << grand_total << endl;
    }
    
    static TeaPurchase* readArrayFromFile(const string& filename, int& count) {
        ifstream inFile(filename, ios::binary);
        if (!inFile) {
            cerr << "Cannot open binary file!" << endl;
            return nullptr;
        }

        inFile.read(reinterpret_cast<char*>(&count), sizeof(count));
        TeaPurchase* purchases = new TeaPurchase[count];
        
        for (int i = 0; i < count; ++i) {
            purchases[i].readFromFile(inFile);
        }
        
        inFile.close();
        return purchases;
    }
};

bool compareByTotal(const TeaPurchase& a, const TeaPurchase& b) {
    return a.total_sum > b.total_sum;
}

int partition(TeaPurchase* arr, int low, int high) {
    TeaPurchase pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (compareByTotal(arr[j], pivot)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(TeaPurchase* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    system("chcp 65001 > nul");
    int count;

    TeaPurchase* purchases = TeaPurchase::readArrayFromFile("tea_purchases.bin", count);
    
    if (purchases == nullptr) {
        return 1;
    }

    quickSort(purchases, 0, count - 1);
    
    TeaPurchase::printHeader();
    
    double grand_total = 0;
    for (int i = 0; i < count; i++) {
        purchases[i].print();
        grand_total += purchases[i].total_sum;
    }
    
    TeaPurchase::printFooter(grand_total);

    delete[] purchases;

    return 0;
}