#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class ComputerEquipment {
private:
    string processorType;
    int ramSize;

public:
    ComputerEquipment(string procType = "", int ram = 0) { // конструктор
        processorType = procType;
        ramSize = ram;
    }

    void outputInfo() const {
        cout << "Тип процессора: " << processorType << endl;
        cout << "Объем оперативной памяти: " << ramSize << " ГБ" << endl;
        cout << "____________________________" << endl;
    }

    string getProcessorType() const {
        return processorType;
    }

    int getRamSize() const {
        return ramSize;
    }

    void setProcessorType(string procType) {
        processorType = procType;
    }

    void setRamSize(int ram) {
        ramSize = ram;
    }
};


bool compareByRam(const ComputerEquipment& a, const ComputerEquipment& b) {
    return a.getRamSize() < b.getRamSize();
}

int main() {
    vector<ComputerEquipment> originalVector;
    
    originalVector.push_back(ComputerEquipment("Intel Core i7", 16));
    originalVector.push_back(ComputerEquipment("AMD Ryzen 5", 8));
    originalVector.push_back(ComputerEquipment("Intel Core i2", 2));
    originalVector.push_back(ComputerEquipment("AMD Ryzen 7", 32));
    originalVector.push_back(ComputerEquipment("Intel Core i5", 12));
    originalVector.push_back(ComputerEquipment("AMD Ryzen 3", 4));

    cout << "Исходный вектор:" << endl;
    for (size_t i = 0; i < originalVector.size(); ++i) {
        cout << "Объект " << i + 1 << ":" << endl;
        originalVector[i].outputInfo();
    }

    vector<ComputerEquipment> newVector;
    
    for (size_t i = 0; i < originalVector.size(); ++i) {
        if (originalVector[i].getRamSize() >= 8) {
            newVector.push_back(originalVector[i]);
        }
    }

    if (newVector.empty()) {
        cout << "Новый вектор пуст!" << endl;
    } else {
        cout << "Новый вектор (до сортировки):" << endl;
        for (size_t i = 0; i < newVector.size(); ++i) {
            cout << "Объект " << i + 1 << ":" << endl;
            newVector[i].outputInfo();
        }

        sort(newVector.begin(), newVector.end(), compareByRam);

        cout << "Новый вектор после сортировки по ОЗУ:" << endl;
        for (size_t i = 0; i < newVector.size(); ++i) {
            cout << "Объект " << i + 1 << ":" << endl;
            newVector[i].outputInfo();
        }
    }

    return 0;
}