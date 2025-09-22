#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <ctime>

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

Square** createSquares(int n) {
    Square** squares = new Square*[n];
    for (int i = 0; i < n; i++) {
        double side = 1 + rand() % 10;
        squares[i] = new Square(side);
    }
    return squares;
}

SquarePrism** createPrisms(int m) {
    SquarePrism** prisms = new SquarePrism*[m];
    for (int i = 0; i < m; i++) {
        double side = 1 + rand() % 10;
        double height = 1 + rand() % 15;
        prisms[i] = new SquarePrism(side, height);
    }
    return prisms;
}

Square* findMaxAreaSquare(Square** squares, int n) {
    if (n == 0) return nullptr;
    
    Square* maxSquare = squares[0];
    for (int i = 1; i < n; i++) {
        if (squares[i]->area() > maxSquare->area()) {
            maxSquare = squares[i];
        }
    }
    return maxSquare;
}

SquarePrism* findMaxVolumePrism(SquarePrism** prisms, int m) {
    if (m == 0) return nullptr;
    
    SquarePrism* maxPrism = prisms[0];
    for (int i = 1; i < m; i++) {
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

    Square** squares = createSquares(n);
    SquarePrism** prisms = createPrisms(m);

    cout << "\n=== ВСЕ КВАДРАТЫ ===" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Квадрат " << i + 1 << ":" << endl;
        squares[i]->printInfo();
    }

    cout << "\n=== ВСЕ ПРИЗМЫ ===" << endl;
    for (int i = 0; i < m; i++) {
        cout << "Призма " << i + 1 << ":" << endl;
        prisms[i]->printInfo();
    }

    Square* maxSquare = findMaxAreaSquare(squares, n);
    SquarePrism* maxPrism = findMaxVolumePrism(prisms, m);

    cout << "\n=== РЕЗУЛЬТАТЫ ===" << endl;
    if (maxSquare) {
        cout << "Квадрат с максимальной площадью:" << endl;
        maxSquare->printInfo();
    }

    if (maxPrism) {
        cout << "Призма с максимальным объемом:" << endl;
        maxPrism->printInfo();
    }

    for (int i = 0; i < n; i++) delete squares[i];
    for (int i = 0; i < m; i++) delete prisms[i];
    
    delete[] squares;
    delete[] prisms;

    return 0;
}