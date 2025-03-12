#include "polynomial.h"
#include <iostream>
#include <clocale> 
#include <limits>

void print_polynomial(const Polynomial& p)
{
    bool first = true;

    for (auto it = p.begin(); it != p.end(); ++it)
    {
        if (!first)
        {
            std::cout << " + ";
        }

        std::cout << (*it).get_k();

        if ((*it).get_x_degree() > 0)
        {
            std::cout << "x^" << (*it).get_x_degree();
        }
        if ((*it).get_y_degree() > 0)
        {
            std::cout << "y^" << (*it).get_y_degree();
        }
        if ((*it).get_z_degree() > 0)
        {
            std::cout << "z^" << (*it).get_z_degree();
        }

        first = false;
    }

    if (first)
    {
        std::cout << "0";
    }

    std::cout << std::endl;
}

Term get_term_from_user()
{
    size_t degree;
    double coefficient;

    std::cout << "Введите степень члена (в виде 3-значного числа, xyz для x^x * y^y * z^z): ";
    std::cin >> degree;


    while (std::cin.fail() || degree > 999 || degree < 0)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Неверный ввод. Пожалуйста, введите корректную степень (3-значное число): ";
        std::cin >> degree;
    }

    std::cout << "Введите коэффициент: ";
    std::cin >> coefficient;

    return Term(degree, coefficient);
}

void menu()
{
    Polynomial p1;
    Polynomial p2;

    int choice = -1;

    while (choice != 0)
    {
        std::cout << "\nМеню:\n"
            << "1. Добавить член в Полином 1\n"
            << "2. Добавить член в Полином 2\n"
            << "3. Показать Полином 1\n"
            << "4. Показать Полином 2\n"
            << "5. Сложить Полиномы\n"
            << "6. Умножить Полином 1 на скаляр\n"
            << "7. Умножить Полином 1 на член\n"
            << "8. Умножить Полиномы\n"
            << "0. Выход\n"
            << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            Term t = get_term_from_user();

            p1.add_term(t);

            std::cout << "Член добавлен в Полином 1.\n";

            break;
        }
        case 2:
        {
            Term t = get_term_from_user();

            p2.add_term(t);

            std::cout << "Член добавлен в Полином 2.\n";

            break;
        }
        case 3:
        {
            std::cout << "Полином 1: ";

            print_polynomial(p1);

            break;
        }
        case 4:
        {
            std::cout << "Полином 2: ";

            print_polynomial(p2);

            break;
        }
        case 5:
        {
            Polynomial sum = p1 + p2;

            std::cout << "Сумма Полиномов: ";

            print_polynomial(sum);

            break;
        }
        case 6:
        {
            double scalar;

            std::cout << "Введите скаляр для умножения Полинома 1: ";
            std::cin >> scalar;

            Polynomial scaled = p1 * scalar;

            std::cout << "Масштабированный Полином 1: ";

            print_polynomial(scaled);

            break;
        }
        case 7:
        {
            Term t = get_term_from_user();
            Polynomial term_product = p1 * t;

            std::cout << "Произведение Полинома 1 и Члена: ";

            print_polynomial(term_product);

            break;
        }
        case 8:
        {
            Polynomial product = p1 * p2;

            std::cout << "Произведение Полиномов: ";

            print_polynomial(product);

            break;
        }
        case 0:
            std::cout << "Выход из программы.\n";

            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";

            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    try
    {
        menu();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}