#include <iostream>
#include <string>

using namespace std;

class ComputerEquipment {
private:
    string processorType;
    int ramSize;

public:
    ComputerEquipment(string procType, int ram) { //конструктр
        processorType = procType;
        ramSize = ram;
    }

    void outputInfo() {
        cout << "Тип процессора: " << processorType << endl;
        cout << "Объем оперативной памяти: " << ramSize << " ГБ" << endl;
        cout << "____________________________" << endl;
    }

    string getProcessorType() {
        return processorType;
    }

    int getRamSize() {
        return ramSize;
    }

    void setProcessorType(string procType) {
        processorType = procType;
    }

    void setRamSize(int ram) {
        ramSize = ram;
    }
};

int main() {
    ComputerEquipment comp1("Intel Core i7", 16);
    ComputerEquipment comp2("AMD Ryzen 5", 8);
    
    cout << "Исходные данные: " << endl;
    cout << "Компьютерная техника 1:" << endl;
    comp1.outputInfo();
    
    cout << "Компьютерная техника 2:" << endl;
    comp2.outputInfo();

    cout << " "<< endl;
    cout << "Получение значений полей:" << endl;
    cout << "Тип процессора comp1: " << comp1.getProcessorType() << endl;
    cout << "ОЗУ comp2: " << comp2.getRamSize() << " ГБ" << endl << endl;
    
    cout << "Изменение значений полей:" << endl;
    comp1.setProcessorType("Intel Core i9");
    comp1.setRamSize(32);
    
    comp2.setProcessorType("AMD Ryzen 7");
    comp2.setRamSize(16);

    cout << "После изменений:" << endl;
    cout << "Компьютерная техника 1:" << endl;
    comp1.outputInfo();
    
    cout << "Компьютерная техника 2:" << endl;
    comp2.outputInfo();
    cout << " "<< endl;

    cout << "Значения после изменений:" << endl;
    cout << "Тип процессора comp1: " << comp1.getProcessorType() << endl;
    cout << "ОЗУ comp1: " << comp1.getRamSize() << " ГБ" << endl;
    cout << "Тип процессора comp2: " << comp2.getProcessorType() << endl;
    cout << "ОЗУ comp2: " << comp2.getRamSize() << " ГБ" << endl;

    return 0;
}
