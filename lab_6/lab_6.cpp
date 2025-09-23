#include <iostream>
#include <stack>
#include <string>

using namespace std;

void displayStack(stack<char> s, const string& name) {
    cout << name << ": ";
    
    stack<char> temp;
    while (!s.empty()) {
        temp.push(s.top());
        s.pop();
    }
    
    while (!temp.empty()) {
        cout << temp.top() << " ";
        temp.pop();
    }
    cout << endl;
}

int main() {
    system("chcp 65001 > nul");
    string input;
    stack<char> stack1, stack2, stack3;
    
    cout << "Введите строку символов: ";
    getline(cin, input);
    
    for (size_t i = 0; i < input.length(); i++) {
        if (i % 2 == 0) {
            stack1.push(input[i]);
        } else {
            stack2.push(input[i]);
        }
    }
    
    cout << "\nИсходные стеки:" << endl;
    displayStack(stack1, "Стек 1");
    displayStack(stack2, "Стек 2");
    
    while (!stack1.empty() || !stack2.empty()) {
        if (!stack2.empty()) {
            stack3.push(stack2.top());
            stack2.pop();
        }
        if (!stack1.empty()) {
            stack3.push(stack1.top());
            stack1.pop();
        }
    }
    
    cout << "\nРезультирующий стек:" << endl;
    displayStack(stack3, "Стек 3");
    
    return 0;
}