#include <iostream>
#include <cmath>
#include <locale>

// Интегрируемая функция F(x) = f(x) * cos(omega * x) или F(x) = f(x) * sin(omega * x)
double F(double(*f)(double), double x, bool forcos, double omega) {
    return forcos ? f(x) * cos(omega * x) : f(x) * sin(omega * x);
}

// Функция для вычисления интеграла методом Файлона
double filone3(double(*f)(double), double a, double b, bool forcos = true, double eps = 1e-12) {
    const int N = 10000; // Максимальное количество подотрезков (можно увеличить при необходимости)
    double result = 0.0;
    double h = (b - a) / N;
    double omega = 2.0 * 3.14159265358979323846 * 10000.0; // Пример значения omega

    for (int i = 0; i < N; ++i) {
        double x1 = a + i * h;
        double x2 = a + (i + 1) * h;

        // Проверка условия (b_k - a_k) * omega >> 2*pi
        if ((x2 - x1) * omega <= 2.0 * 3.14159265358979323846) {
            std::cerr << "Ошибка: Условие (b_k - a_k) * omega >> 2*pi не выполняется на подотрезке." << std::endl;
            return 0.0;
        }

        // Вычисление интеграла на подотрезке методом Файлона
        double integral = 0.0;
        double dx = (x2 - x1) / 4.0; // Шаг интегрирования 
        for (int j = 0; j < 4; ++j) {
            double xi = x1 + j * dx;
            integral += F(f, xi, forcos, omega);
        }
        integral *= (2.0 * dx / 45.0);

        result += integral;
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    double a = 0.0;
    double b = 1.0;
    double integral = filone3([](double x) { return x * x; }, a, b, true);

    std::cout << "Интеграл: " << integral << std::endl;
    return 0;
}
