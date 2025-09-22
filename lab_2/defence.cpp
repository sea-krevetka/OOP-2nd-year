#include <iostream>
#include <string>
using namespace std;

class Pharmacy {
protected:
    string name;
    string phone;
    string address;
    string workingHours;

public:
    Pharmacy() : name(""), phone(""), address(""), workingHours("") {}
    Pharmacy(string n, string p, string a, string wh) 
        : name(n), phone(p), address(a), workingHours(wh) {}
    
    void setName(string n) { name = n; }
    void setPhone(string p) { phone = p; }
    void setAddress(string a) { address = a; }
    void setWorkingHours(string wh) { workingHours = wh; }
    
    string getName() const { return name; }
    string getPhone() const { return phone; }
    string getAddress() const { return address; }
    string getWorkingHours() const { return workingHours; }
    
    virtual void display() const {
        cout << "Название: " << name << endl;
        cout << "Телефон: " << phone << endl;
        cout << "Адрес: " << address << endl;
        cout << "Время работы: " << workingHours << endl;
    }
};

class PrivatePharmacy : public Pharmacy {
private:
    string ownerName;

public:
    PrivatePharmacy() : Pharmacy(), ownerName("") {}

    PrivatePharmacy(string n, string p, string a, string wh, string owner)
        : Pharmacy(n, p, a, wh), ownerName(owner) {}
    
    void setOwnerName(string owner) { ownerName = owner; }
    
    string getOwnerName() const { return ownerName; }
    
    void display() const override {
        Pharmacy::display();
        cout << "ФИО владельца: " << ownerName << endl;
    }
};

int main() {
    cout << "=== Демонстрация базового класса Аптеки ===" << endl;
    Pharmacy pharmacy1;
    pharmacy1.setName("Домик Травника");
    pharmacy1.setPhone("Три раза постучать в дверь");
    pharmacy1.setAddress("Справа от дома Старосты");
    pharmacy1.setWorkingHours("09:00-21:00");
    pharmacy1.display();
    
    cout << endl;
    
    Pharmacy pharmacy2("Дикий огонь", "Дважды постучать", 
                      "Подземье Белобога", "08:00-22:00");
    pharmacy2.display();
    
    cout << endl << "=== Демонстрация класса-наследника Частная_аптека ===" << endl;
    
    PrivatePharmacy private1;
    private1.setName("Хижина 'Бубу'");
    private1.setPhone("GL ttp-2");
    private1.setAddress("Северная часть гавани Ли Юэ");
    private1.setWorkingHours("10:00-20:00");
    private1.setOwnerName("Бай Чжу");
    private1.display();
    
    cout << endl;
    
    PrivatePharmacy private2("Jarilo-VI", "-", 
                            "Белобог", "09:00-19:00", 
                            "Наташа");
    private2.display();
    
    cout << endl << "=== Демонстрация полиморфизма ===" << endl;
    
    Pharmacy* pharmacies[3];
    pharmacies[0] = &pharmacy1;
    pharmacies[1] = &private1;
    pharmacies[2] = &private2;
    
    for (int i = 0; i < 3; i++) {
        cout << "Аптека " << i+1 << ":" << endl;
        pharmacies[i]->display();
        cout << endl;
    }
    
    return 0;
}