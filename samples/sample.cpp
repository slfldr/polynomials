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

    std::cout << "Ââåäèòå ñòåïåíü ÷ëåíà (â âèäå 3-çíà÷íîãî ÷èñëà, xyz äëÿ x^x * y^y * z^z): ";
    std::cin >> degree;

    while (std::cin.fail() || degree > 999 || degree < 0)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Íåâåðíûé ââîä. Ïîæàëóéñòà, ââåäèòå êîððåêòíóþ ñòåïåíü (3-çíà÷íîå ÷èñëî): ";
        std::cin >> degree;
    }

    std::cout << "Ââåäèòå êîýôôèöèåíò: ";
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
        std::cout << "\nÌåíþ:\n"
            << "1. Äîáàâèòü ÷ëåí â Ïîëèíîì 1\n"
            << "2. Äîáàâèòü ÷ëåí â Ïîëèíîì 2\n"
            << "3. Ïîêàçàòü Ïîëèíîì 1\n"
            << "4. Ïîêàçàòü Ïîëèíîì 2\n"
            << "5. Ñëîæèòü Ïîëèíîìû\n"
            << "6. Óìíîæèòü Ïîëèíîì 1 íà ñêàëÿð\n"
            << "7. Óìíîæèòü Ïîëèíîì 1 íà ÷ëåí\n"
            << "8. Óìíîæèòü Ïîëèíîìû\n"
            << "0. Âûõîä\n"
            << "Ââåäèòå âàø âûáîð: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            Term t = get_term_from_user();

            p1.add_term(t);

            std::cout << "×ëåí äîáàâëåí â Ïîëèíîì 1.\n";

            break;
        }
        case 2:
        {
            Term t = get_term_from_user();

            p2.add_term(t);

            std::cout << "×ëåí äîáàâëåí â Ïîëèíîì 2.\n";

            break;
        }
        case 3:
        {
            std::cout << "Ïîëèíîì 1: ";

            print_polynomial(p1);

            break;
        }
        case 4:
        {
            std::cout << "Ïîëèíîì 2: ";

            print_polynomial(p2);

            break;
        }
        case 5:
        {
            Polynomial sum = p1 + p2;

            std::cout << "Ñóììà Ïîëèíîìîâ: ";

            print_polynomial(sum);

            break;
        }
        case 6:
        {
            double scalar;

            std::cout << "Ââåäèòå ñêàëÿð äëÿ óìíîæåíèÿ Ïîëèíîìà 1: ";
            std::cin >> scalar;

            Polynomial scaled = p1 * scalar;

            std::cout << "Ìàñøòàáèðîâàííûé Ïîëèíîì 1: ";

            print_polynomial(scaled);

            break;
        }
        case 7:
        {
            Term t = get_term_from_user();
            Polynomial term_product = p1 * t;

            std::cout << "Ïðîèçâåäåíèå Ïîëèíîìà 1 è ×ëåíà: ";

            print_polynomial(term_product);

            break;
        }
        case 8:
        {
            Polynomial product = p1 * p2;

            std::cout << "Ïðîèçâåäåíèå Ïîëèíîìîâ: ";

            print_polynomial(product);

            break;
        }
        case 0:
            std::cout << "Âûõîä èç ïðîãðàììû.\n";

            break;
        default:
            std::cout << "Íåâåðíûé âûáîð. Ïîïðîáóéòå ñíîâà.\n";

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
        std::cerr << "Îøèáêà: " << e.what() << std::endl;
    }

    return 0;
}
