#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

class Bus {
private:
    int busNumber;
    string driverName;
    int routeNumber;
    
public:
    Bus(int number, const string& name, int route) 
        : busNumber(number), driverName(name), routeNumber(route) {}
    
    int getBusNumber() const { return busNumber; }
    string getDriverName() const { return driverName; }
    int getRouteNumber() const { return routeNumber; }
    
    void display() const {
        cout << "Номер автобуса: " << busNumber 
             << ", Водитель: " << driverName 
             << ", Маршрут: " << routeNumber << endl;
    }
    
    bool operator==(int number) const {
        return busNumber == number;
    }
};

class BusDepot {
private:
    list<Bus> busesInDepot;
    list<Bus> busesOnRoute;
    
public:
    void addBusToDepot(int number, const string& name, int route) {
        busesInDepot.emplace_back(number, name, route);
        cout << "Автобус добавлен в парк." << endl;
    }
    
    void moveBusToRoute(int busNumber) {
        auto it = find(busesInDepot.begin(), busesInDepot.end(), busNumber);
        
        if (it != busesInDepot.end()) {
            busesOnRoute.push_back(*it);
            busesInDepot.erase(it);
            cout << "Автобус " << busNumber << " выехал на маршрут." << endl;
        } else {
            cout << "Автобус с номером " << busNumber << " не найден в парке." << endl;
        }
    }
    
    void moveBusToDepot(int busNumber) {
        auto it = find(busesOnRoute.begin(), busesOnRoute.end(), busNumber);
        
        if (it != busesOnRoute.end()) {
            busesInDepot.push_back(*it);
            busesOnRoute.erase(it);
            cout << "Автобус " << busNumber << " вернулся в парк." << endl;
        } else {
            cout << "Автобус с номером " << busNumber << " не найден на маршруте." << endl;
        }
    }
    
    void displayBusesInDepot() const {
        if (busesInDepot.empty()) {
            cout << "В парке нет автобусов." << endl;
            return;
        }
        
        cout << "=== АВТОБУСЫ В ПАРКЕ ===" << endl;
        for (const auto& bus : busesInDepot) {
            bus.display();
        }
        cout << "Всего: " << busesInDepot.size() << " автобусов" << endl;
    }
    
    void displayBusesOnRoute() const {
        if (busesOnRoute.empty()) {
            cout << "На маршруте нет автобусов." << endl;
            return;
        }
        
        cout << "=== АВТОБУСЫ НА МАРШРУТЕ ===" << endl;
        for (const auto& bus : busesOnRoute) {
            bus.display();
        }
        cout << "Всего: " << busesOnRoute.size() << " автобусов" << endl;
    }
    
    void getStatistics() const {
        cout << "Статистика:" << endl;
        cout << "В парке: " << busesInDepot.size() << " автобусов" << endl;
        cout << "На маршруте: " << busesOnRoute.size() << " автобусов" << endl;
        cout << "Всего: " << (busesInDepot.size() + busesOnRoute.size()) << " автобусов" << endl;
    }
};

void displayMenu() {
    cout << "\n=== МЕНЮ УПРАВЛЕНИЯ АВТОБУСНЫМ ПАРКОМ ===" << endl;
    cout << "1. Добавить автобус в парк" << endl;
    cout << "2. Отправить автобус на маршрут" << endl;
    cout << "3. Вернуть автобус в парк" << endl;
    cout << "4. Показать автобусы в парке" << endl;
    cout << "5. Показать автобусы на маршруте" << endl;
    cout << "6. Показать статистику" << endl;
    cout << "7. Выход" << endl;
    cout << "Выберите действие: ";
}

int main() {
    system("chcp 65001 > nul");
    BusDepot depot;
    int choice;
    
    cout << "Начальное формирование данных..." << endl;
    depot.addBusToDepot(456, "Фрогуна В.К", 55);
    depot.addBusToDepot(865, "Флинс К.Ч", 23);
    depot.addBusToDepot(879, "Вовчик М.В", 42);
    depot.addBusToDepot(598, "Некит Н.н", 39);
    
    do {
        displayMenu();
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: {
                int number, route;
                string name;
                
                cout << "Введите номер автобуса: ";
                cin >> number;
                cout << "Введите ФИО водителя: ";
                cin.ignore();
                getline(cin, name);
                cout << "Введите номер маршрута: ";
                cin >> route;
                
                depot.addBusToDepot(number, name, route);
                break;
            }
            case 2: {
                int number;
                cout << "Введите номер автобуса для отправки на маршрут: ";
                cin >> number;
                depot.moveBusToRoute(number);
                break;
            }
            case 3: {
                int number;
                cout << "Введите номер автобуса для возврата в парк: ";
                cin >> number;
                depot.moveBusToDepot(number);
                break;
            }
            case 4:
                depot.displayBusesInDepot();
                break;
            case 5:
                depot.displayBusesOnRoute();
                break;
            case 6:
                depot.getStatistics();
                break;
            case 7:
                cout << "Выход из программы..." << endl;
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    } while (choice != 7);
    
    return 0;
}