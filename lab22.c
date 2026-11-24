#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>

typedef double (*TFunc)(double);

double calc_y(double x);
double calc_v(double x);
double calc_s(double x);
void print_table(double a, double b, double h, TFunc f);
void calc_range(double a, double b, double h, TFunc f);
TFunc select_function(void);

int main()
{
    int menu;
    double x, a, b, h, result;
    TFunc f;
    setlocale(LC_ALL, "ru_RU.UTF-8");

    do
    {
        printf("\n--- Лабораторная работа 22 ---\n");
        printf("1 - Вычислить значение функции\n");
        printf("2 - Табулировать функцию\n");
        printf("3 - Модуль разности максимума и минимума\n");
        printf("0 - Выход\nВаш выбор: ");
        if (scanf("%d", &menu) != 1) return 0;
        if (menu == 0) break;
        if (menu < 1 || menu > 3)
        {
            printf("Неверный пункт меню.\n");
            continue;
        }
        f = select_function();
        if (f == NULL) continue;
        if (menu == 1)
        {
            printf("Введите x: ");
            if (scanf("%lf", &x) != 1) return 0;
            result = f(x);
            if (isfinite(result)) printf("Результат: %.6lf\n", result);
            else printf("Функция не определена в этой точке.\n");
        }
        else
        {
            printf("Введите начало интервала: ");
            if (scanf("%lf", &a) != 1) return 0;
            printf("Введите конец интервала: ");
            if (scanf("%lf", &b) != 1) return 0;
            printf("Введите шаг: ");
            if (scanf("%lf", &h) != 1) return 0;
            if (a > b || h <= 0 || !isfinite(a) || !isfinite(b) || !isfinite(h))
            {
                printf("Ошибка: интервал или шаг заданы неверно.\n");
                continue;
            }
            if ((b - a) / h > 100000)
            {
                printf("Слишком много точек. Увеличьте шаг.\n");
                continue;
            }
            if (menu == 2) print_table(a, b, h, f);
            else calc_range(a, b, h, f);
        }
    } while (menu != 0);
    return 0;
}

double calc_y(double x)
{
    if (x <= 0) return NAN;
    return log(sqrt(x * x * x));
}

double calc_v(double x)
{
    double t;
    if (x < 0) return exp(cos(x));
    if (x <= 1) return -2 * x;
    t = tan(x * x - 1);
    if (!isfinite(t) || t < 0) return NAN;
    return sqrt(t);
}

double calc_s(double x)
{
    double t;
    if (x == -1) return NAN;
    t = (x - 1) / (x + 1);
    return t + pow(t, 3) / 3 + pow(t, 5) / 5 + pow(t, 7) / 7;
}

TFunc select_function()
{
    int choice;
    printf("Выберите функцию: 1 - Y(x), 2 - V(x), 3 - S(x): ");
    if (scanf("%d", &choice) != 1) return NULL;
    switch (choice)
    {
    case 1: return calc_y;
    case 2: return calc_v;
    case 3: return calc_s;
    default: printf("Неверный выбор функции.\n"); return NULL;
    }
}

void print_table(double a, double b, double h, TFunc f)
{
    int i, n = (int)((b - a) / h);
    double x, y;
    printf("\n         x              f(x)\n");
    for (i = 0; i <= n; i++)
    {
        x = a + i * h;
        y = f(x);
        if (isfinite(y)) printf("%12.6lf     %12.6lf\n", x, y);
        else printf("%12.6lf     не определена\n", x);
    }
}

void calc_range(double a, double b, double h, TFunc f)
{
    int i, n = (int)((b - a) / h), found = 0;
    double x, y, ymin = 0, ymax = 0;
    for (i = 0; i <= n; i++)
    {
        x = a + i * h;
        y = f(x);
        if (!isfinite(y)) continue;
        if (!found)
        {
            ymin = y;
            ymax = y;
            found = 1;
        }
        if (y < ymin) ymin = y;
        if (y > ymax) ymax = y;
    }
    if (!found) printf("Нет определённых значений на выбранных точках.\n");
    else
    {
        printf("Минимальное значение: %.6lf\n", ymin);
        printf("Максимальное значение: %.6lf\n", ymax);
        printf("Модуль разности: %.6lf\n", fabs(ymax - ymin));
        printf("Значения найдены по точкам с заданным шагом.\n");
    }
}
