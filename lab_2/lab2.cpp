#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

class Square {
protected:
    double side;

public:
    Square(double s) : side(s) {}

    virtual double diagonal() const {
        return side * sqrt(2);
    }

    virtual double perimeter() const {
        return 4 * side;
    }

    virtual double area() const {
        return side * side;
    }

    virtual void printInfo() const {
        cout << "Квадрат:" << endl;
        cout << "  Сторона: " << side << endl;
        cout << "  Диагональ: " << fixed << setprecision(2) << diagonal() << endl;
        cout << "  Периметр: " << perimeter() << endl;
        cout << "  Площадь: " << area() << endl;
        cout << endl;
    }

    double getSide() const { return side; }
};

class SquarePrism : public Square {
private:
    double height;

public:
    SquarePrism(double s, double h) : Square(s), height(h) {}

    double area() const override {
        return 2 * (side * side) + 4 * side * height;
    }

    double volume() const {
        return side * side * height;
    }

    void printInfo() const override {
        cout << "Квадратная призма:" << endl;
        cout << "  Сторона основания: " << side << endl;
        cout << "  Высота: " << height << endl;
        cout << "  Диагональ основания: " << fixed << setprecision(2) << diagonal() << endl;
        cout << "  Площадь поверхности: " << area() << endl;
        cout << "  Объем: " << volume() << endl;
        cout << endl;
    }

    double getHeight() const { return height; }
};

vector<Square*> createSquares(int n) {
    vector<Square*> squares;
    for (int i = 0; i < n; i++) {
        double side = 1 + rand() % 10;
        squares.push_back(new Square(side));
    }
    return squares;
}

vector<SquarePrism*> createPrisms(int m) {
    vector<SquarePrism*> prisms;
    for (int i = 0; i < m; i++) {
        double side = 1 + rand() % 10;
        double height = 1 + rand() % 15;
        prisms.push_back(new SquarePrism(side, height));
    }
    return prisms;
}

Square* findMaxAreaSquare(const vector<Square*>& squares) {
    if (squares.empty()) return nullptr;
    
    Square* maxSquare = squares[0];
    for (size_t i = 1; i < squares.size(); i++) {
        if (squares[i]->area() > maxSquare->area()) {
            maxSquare = squares[i];
        }
    }
    return maxSquare;
}

SquarePrism* findMaxVolumePrism(const vector<SquarePrism*>& prisms) {
    if (prisms.empty()) return nullptr;
    
    SquarePrism* maxPrism = prisms[0];
    for (size_t i = 1; i < prisms.size(); i++) {
        if (prisms[i]->volume() > maxPrism->volume()) {
            maxPrism = prisms[i];
        }
    }
    return maxPrism;
}

int main() {
    srand(time(0));

    int n, m;
    cout << "Введите количество квадратов (N): ";
    cin >> n;
    cout << "Введите количество призм (M): ";
    cin >> m;

    vector<Square*> squares = createSquares(n);
    vector<SquarePrism*> prisms = createPrisms(m);

    cout << "\n=== ВСЕ КВАДРАТЫ ===" << endl;
    for (size_t i = 0; i < squares.size(); i++) {
        cout << "Квадрат " << i + 1 << ":" << endl;
        squares[i]->printInfo();
    }

    cout << "\n=== ВСЕ ПРИЗМЫ ===" << endl;
    for (size_t i = 0; i < prisms.size(); i++) {
        cout << "Призма " << i + 1 << ":" << endl;
        prisms[i]->printInfo();
    }

    Square* maxSquare = findMaxAreaSquare(squares);
    SquarePrism* maxPrism = findMaxVolumePrism(prisms);

    cout << "\n=== РЕЗУЛЬТАТЫ ===" << endl;
    if (maxSquare) {
        cout << "Квадрат с максимальной площадью:" << endl;
        maxSquare->printInfo();
    }

    if (maxPrism) {
        cout << "Призма с максимальным объемом:" << endl;
        maxPrism->printInfo();
    }

    for (auto sq : squares) delete sq;
    for (auto pr : prisms) delete pr;

    return 0;
}