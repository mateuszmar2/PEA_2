#include "Towns.h"
#include "Simulated_Annealing.h"
#include "Tabu_Search.h"
#include "Neighbour.h"

#include <iostream>
#include <limits>
#include <chrono>

using namespace std;

void menuSA(Towns &towns, int &stop_time, double &temperature, double &min_temperature, double &temperature_change, int &maxit, NeighbourOperation &operation)
{
    int action;
    int value;
    double temp;
    do
    {
        cout << endl
             << "Which action you want to perform? Type appropriate number " << endl;
        cout << "1 - Run Simulated Annealing algorithm " << endl;
        cout << "2 - Modify temperature, current = " << temperature << endl;
        cout << "3 - Modify minimum temperature, current = " << min_temperature << endl;
        cout << "4 - Modify temperature change, current = " << temperature_change << endl;
        cout << "5 - Modify maximum number of iterations, current = " << maxit << endl;
        cout << "6 - Modify stop time, current = " << stop_time << endl;
        cout << "7 - Modify neighbour operation, current = ";
        switch (operation)
        {
        case 1:
            cout << "Swap Operation" << endl;
            break;
        case 2:
            cout << "Reverse Operation" << endl;
            break;
        case 3:
            cout << "Insert Operation" << endl;
            break;
        }
        cout << "8 - Exit SA mode " << endl;
        cout << "SA> ";
        cin >> action;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;
        switch (action)
        {
        case 1: // algorytm
        {
            if (towns.getTowns().empty())
            {
                cout << "Load data first" << endl;
                break;
            }
            std::chrono::steady_clock::time_point start =
                std::chrono::steady_clock::now();
            SimulatedAnnealing sa(towns.getTowns(), operation, temperature, min_temperature, temperature_change, maxit, stop_time);
            sa.startSA();
            std::chrono::steady_clock::time_point end =
                std::chrono::steady_clock::now();
            sa.printRoute();
            std::cout << "Execution time: "
                      << std::chrono::duration_cast<std::chrono::microseconds>(
                             end - start)
                             .count()
                      << "us\n";
            if (towns.getOptimalResult() != 0)
                cout << "Relative error: " << float(abs(sa.getRouteCost() - towns.getOptimalResult())) / towns.getOptimalResult() * 100 << "%" << endl;
            break;
        }
        case 2: // temperatura
            cout << "Enter new temperature: ";
            cin >> temp;
            if (temp <= 0 || cin.fail())
            {
                cout << "Invalid temperature" << endl;
                break;
            }
            temperature = temp;
            break;
        case 3: // min_temp
            cout << "Enter new minimum temperature: ";
            cin >> temp;
            if (temp <= 0 || cin.fail())
            {
                cout << "Invalid minimum temperature" << endl;
                break;
            }
            min_temperature = temp;
            break;
        case 4: // temperature change
            cout << "Enter new temperature change: ";
            cin >> temp;
            if (temp <= 0 || cin.fail())
            {
                cout << "Invalid temperature change" << endl;
                break;
            }
            temperature_change = temp;
            break;
        case 5: // maxit
            cout << "Enter new maximum number of iterations: ";
            cin >> value;
            if (value <= 0 || cin.fail())
            {
                cout << "Invalid maximum number of iterations" << endl;
                break;
            }
            maxit = value;
            break;
        case 6: // stop time
            cout << "Enter new stop time: ";
            cin >> value;
            if (value <= 0 || cin.fail())
            {
                cout << "Invalid stop time" << endl;
                break;
            }
            stop_time = value;
            break;
        case 7: // neighbour operation
            cout << "1 - Swap Operation" << endl;
            cout << "2 - Reverse Operation" << endl;
            cout << "3 - Insert Operation" << endl;
            cout << "Enter new neighbour operation: ";
            cin >> value;
            if (value <= 0 || cin.fail() || value > 3)
            {
                cout << "Invalid neighbour operation" << endl;
                break;
            }
            switch (value)
            {
            case 1:
                operation = SwapOperation;
                break;
            case 2:
                operation = ReverseOperation;
                break;
            case 3:
                operation = InsertOperation;
                break;
            }
            break;
        case 8: // wyjście
            break;
        default:
            cout << "Type appropriate number" << endl;
            break;
        }
    } while (action != 8);
}

void menuTS(Towns &towns, int &stop_time, int &maxit, int &tabu_lifetime, NeighbourOperation &operation)
{
    int action;
    int value;
    // double temp;
    do
    {
        cout << endl
             << "Which action you want to perform? Type appropriate number " << endl;
        cout << "1 - Run Tabu Search algorithm " << endl;
        // cout << "2 - Modify temperature, current = " << temperature << endl;
        // cout << "3 - Modify minimum temperature, current = " << min_temperature << endl;
        // cout << "4 - Modify temperature change, current = " << temperature_change << endl;
        cout << "4 - Modify tabu lifetime, current = " << tabu_lifetime << endl;
        cout << "5 - Modify maximum number of iterations, current = " << maxit << endl;
        cout << "6 - Modify stop time, current = " << stop_time << endl;
        cout << "7 - Exit SA mode " << endl;
        cout << "TS> ";
        cin >> action;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;
        switch (action)
        {
        case 1: // algorytm
        {
            if (towns.getTowns().empty())
            {
                cout << "Load data first" << endl;
                break;
            }
            std::chrono::steady_clock::time_point start =
                std::chrono::steady_clock::now();
            TabuSearch ts(towns.getTowns());
            ts.setAttributes(maxit, stop_time, tabu_lifetime);
            ts.startTS();
            std::chrono::steady_clock::time_point end =
                std::chrono::steady_clock::now();
            ts.printRoute();
            std::cout << "Execution time: "
                      << std::chrono::duration_cast<std::chrono::microseconds>(
                             end - start)
                             .count()
                      << "us\n";
            if (towns.getOptimalResult() != 0)
                cout << "Relative error: " << float(abs(ts.getRouteCost() - towns.getOptimalResult())) / towns.getOptimalResult() * 100 << "%" << endl;
            break;
        }
        // case 2: // temperatura
        //     cout << "Enter new temperature: ";
        //     cin >> temp;
        //     if (temp <= 0 || cin.fail())
        //     {
        //         // cin.clear();
        //         // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        //         cout << "Invalid temperature" << endl;
        //         break;
        //     }
        //     temperature = temp;
        //     break;
        // case 3: // min_temp
        //     cout << "Enter new minimum temperature: ";
        //     cin >> temp;
        //     if (temp <= 0 || cin.fail())
        //     {
        //         // cin.clear();
        //         // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        //         cout << "Invalid minimum temperature" << endl;
        //         break;
        //     }
        //     min_temperature = temp;
        //     break;
        case 4: // tabu lifetime
            cout << "Enter new tabu lifetime: ";
            cin >> value;
            if (value <= 0 || cin.fail())
            {
                // cin.clear();
                // cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid tabu lifetime" << endl;
                break;
            }
            tabu_lifetime = value;
            break;
        case 5: // maxit
            cout << "Enter new maximum number of iterations: ";
            cin >> value;
            if (value <= 0 || cin.fail())
            {
                // cin.clear();
                // cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid maximum number of iterations" << endl;
                break;
            }
            maxit = value;
            break;
        case 6: // stop time
            cout << "Enter new stop time: ";
            cin >> value;
            if (value <= 0 || cin.fail())
            {
                // cin.clear();
                // cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid stop time" << endl;
                break;
            }

            stop_time = value;
            break;
        case 7: // wyjście
            break;
        default:
            cout << "Type appropriate number" << endl;
            break;
        }
    } while (action != 7);
}

void menu()
{
    Towns towns;
    char choice;
    char filename[50];
    double temperature = 1000;
    double min_temperature = 1;
    double temperature_change = 0.999;
    int maxit = 5000;
    int stop_time = 60;
    int tabu_lifetime = 100;
    NeighbourOperation operation = SwapOperation;
    do
    {
        cout << endl
             << "Which action you want to perform? Type appropriate number " << endl;
        cout << "p - Print data " << endl;
        cout << "l - Load data from file " << endl;
        cout << "s - Simulated Annealing menu " << endl;
        cout << "t - Tabu Search algorithm " << endl;
        cout << "e - Exit the program " << endl;
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
        case 's': // Simulated Annealing menu
        {
            menuSA(towns, stop_time, temperature, min_temperature, temperature_change, maxit, operation);
            break;
        }
        case 't': // Tabu Search
        {
            menuTS(towns, stop_time, maxit, tabu_lifetime, operation);
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
