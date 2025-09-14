#include <iostream>
#include <cmath>
#include <complex>

using namespace std;

struct irrational_nums {
    double real;
    double img;
};

double calculate_module(const irrational_nums& num) {
    return sqrt(num.real * num.real + num.img * num.img);
}

irrational_nums* find_extreme_modules(irrational_nums complex_arr[], int size) {
    static irrational_nums result[2];
    double big_module = 0.0;
    double small_module = calculate_module(complex_arr[0]);
    int big_index = 0;
    int small_index = 0;
    
    for (int i = 0; i < size; i++) {
        double current_module = calculate_module(complex_arr[i]);
        
        if (current_module > big_module) {
            big_module = current_module;
            big_index = i;
        }
        if (current_module < small_module) {
            small_module = current_module;
            small_index = i;
        }
    }
    
    result[0] = complex_arr[small_index];
    result[1] = complex_arr[big_index];
    
    return result;
}

int main() {
    irrational_nums complex_arr[] = {
        {1.0, 2.0},
        {32.0, -6.0},
        {0.0, 1.0},
        {5.0, -8.0},
        {0.0, -5.0},
        {42.0, 23.0}
    };

    const int ARRAY_SIZE = sizeof(complex_arr) / sizeof(complex_arr[0]);
    
    irrational_nums* final_arr = find_extreme_modules(complex_arr, ARRAY_SIZE);

    cout << "Число с наименьшим модулем: (" << final_arr[0].real << ", " << final_arr[0].img << "i)" << endl;
    cout << "Число с наибольшим модулем: (" << final_arr[1].real << ", " << final_arr[1].img << "i)" << endl;
    
    cout << "Наименьший модуль: " << calculate_module(final_arr[0]) << endl;
    cout << "Наибольший модуль: " << calculate_module(final_arr[1]) << endl;

    return 0;
}