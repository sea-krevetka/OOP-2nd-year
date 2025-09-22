#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class TeaPurchase {
private:
    string tea_type;
    string package_type;
    string producer;
    double price;
    int quantity;
    double total_sum;

public:
    TeaPurchase() {
        price = 0;
        quantity = 0;
        total_sum = 0;
    }

    void calculateTotal() {
        total_sum = price * quantity;
    }

    void print() const {
        cout << tea_type << "\t" << package_type << "\t" << producer << "\t"
             << price << "\t" << quantity << "\t" << total_sum << endl;
    }

    bool readFromTextFile(ifstream& inFile) {
        if (!getline(inFile, tea_type)) return false;
        if (!getline(inFile, package_type)) return false;
        if (!getline(inFile, producer)) return false;
        if (!(inFile >> price)) return false;
        if (!(inFile >> quantity)) return false;
        inFile.ignore();
        calculateTotal();
        return true;
    }

    void writeToBinaryFile(ofstream& outFile) const {
        size_t size = tea_type.size();
        outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
        outFile.write(tea_type.c_str(), size);

        size = package_type.size();
        outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
        outFile.write(package_type.c_str(), size);

        size = producer.size();
        outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
        outFile.write(producer.c_str(), size);

        outFile.write(reinterpret_cast<const char*>(&price), sizeof(price));
        outFile.write(reinterpret_cast<const char*>(&quantity), sizeof(quantity));
        outFile.write(reinterpret_cast<const char*>(&total_sum), sizeof(total_sum));
    }

    static int readCountFromFile(ifstream& inFile) {
        int count;
        inFile >> count;
        inFile.ignore();
        return count;
    }

    static void writeCountToBinaryFile(ofstream& outFile, int count) {
        outFile.write(reinterpret_cast<const char*>(&count), sizeof(count));
    }
};

int main() {
    ifstream inFile("tea_purchases.txt");
    if (!inFile) {
        cerr << "Cannot open text file!" << endl;
        return 1;
    }

    int count = TeaPurchase::readCountFromFile(inFile);

    TeaPurchase* purchases = new TeaPurchase[count];
    
    for (int i = 0; i < count; ++i) {
        if (!purchases[i].readFromTextFile(inFile)) {
            cerr << "Error reading data for purchase " << i + 1 << endl;
            delete[] purchases;
            inFile.close();
            return 1;
        }
    }
    inFile.close();

    ofstream outFile("tea_purchases.bin", ios::binary);
    if (!outFile) {
        cerr << "Cannot open binary file for writing!" << endl;
        delete[] purchases;
        return 1;
    }

    TeaPurchase::writeCountToBinaryFile(outFile, count);

    for (int i = 0; i < count; ++i) {
        purchases[i].writeToBinaryFile(outFile);
    }

    outFile.close();
    delete[] purchases;
    
    cout << "Binary file 'tea_purchases.bin' has been created successfully." << endl;

    return 0;
}