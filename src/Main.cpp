#include "Towns.h"
#include "Simulated_Annealing.h"

#include <iostream>
#include <limits>
#include <chrono>

using namespace std;

void menu()
{
    Towns towns;
    char choice;
    char filename[50];
    do
    {
        cout << endl
             << "Which action you want to perform? Type appropriate number " << endl;
        cout << "p - Print data " << endl;
        cout << "l - Load data from file " << endl;
        cout << "g - Generate random data" << endl;
        cout << "s - Simulated Annealing algorithm " << endl;
        cout << "t - Tabu Search algorithm " << endl;
        cout << "c - Set stop criterion" << endl;
        cout << "e - Exit the program " << endl;
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 'p': // wypisanie
            if (towns.getTowns().empty())
            {
                cout << "Load data first" << endl;
                break;
            }
            towns.printData();
            break;
        case 'l': // załadowanie danych z pliku
            cout << "Enter file name: ";
            cin >> filename;
            cout << endl;
            towns.loadDataFromFile(filename);
            break;
        case 'g': // wygenerowanie zestawu losowych danych
        {
            int value = 0;
            cout << "Enter how many towns you want to create: ";
            cin >> value;
            if (value <= 0)
            {
                cout << "Invalid number of towns" << endl;
                break;
            }
            towns.generateRandomData(value);
            towns.printData();
            break;
        }
        case 's': // Simulated Annealing
        {
            if (towns.getTowns().empty())
            {
                cout << "Load data first" << endl;
                break;
            }
            std::chrono::steady_clock::time_point start =
                std::chrono::steady_clock::now();
            SimulatedAnnealing sa(towns.getTowns());
            sa.startSA();
            std::chrono::steady_clock::time_point end =
                std::chrono::steady_clock::now();
            sa.printRoute();
            std::cout << "Execution time: "
                      << std::chrono::duration_cast<std::chrono::microseconds>(
                             end - start)
                             .count()
                      << "us\n";
            break;
        }
        case 't': // Tabu Search
        {
            if (towns.getTowns().empty())
            {
                cout << "Load data first" << endl;
                break;
            }
            std::chrono::steady_clock::time_point start =
                std::chrono::steady_clock::now();
            // TO DO TS
            std::chrono::steady_clock::time_point end =
                std::chrono::steady_clock::now();
            // TO DO TS PRINT
            std::cout << "Execution time: "
                      << std::chrono::duration_cast<std::chrono::microseconds>(
                             end - start)
                             .count()
                      << "us\n";
            break;
        }
        case 'c': // ustawianie kryterium stopu
        {
            break;
        }
        case 'e': // wyjście
            break;
        default:
            cout << "Type appropriate number" << endl;
            break;
        }
    } while (choice != 'e');
}

int main()
{
    menu();

    return 0;
}
