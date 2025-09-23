#include <iostream>
#include <queue>
#include <string>
using namespace std;

void printQueue(queue<char> q) {
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

int main() {
    queue<char> queue1, queue2, queue3;
    string input;

    cout << "Введите символы для первой очереди: ";
    cin >> input;
    for (char ch : input) {
        queue1.push(ch);
    }

    cout << "Введите символы для второй очереди: ";
    cin >> input;
    for (char ch : input) {
        queue2.push(ch);
    }

    cout << "\nПервая очередь (до изменений): ";
    printQueue(queue1);
    
    cout << "Вторая очередь (до изменений): ";
    printQueue(queue2);

    queue<char> temp1 = queue1;
    queue<char> temp2 = queue2;

    while (!temp1.empty() || !temp2.empty()) {
        if (!temp2.empty()) {
            queue3.push(temp2.front());
            temp2.pop();
        }
        if (!temp1.empty()) {
            queue3.push(temp1.front());
            temp1.pop();
        }
    }

    cout << "\nПервая очередь (после обработки): ";
    printQueue(temp1);
    cout << "Вторая очередь (после обработки): ";
    printQueue(temp2);
    cout << "Третья очередь (чередование второй и первой): ";
    printQueue(queue3);

    return 0;
}