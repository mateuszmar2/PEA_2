#include "Simulated_Annealing.h"

#include <iostream>
#include <algorithm>
#include <ctime>
#include <math.h>

using namespace std;

SimulatedAnnealing::SimulatedAnnealing(vector<vector<int>> towns)
{
    srand(time(NULL));
    matrix = towns;
    number_of_towns = matrix[0].size();
    temperature = 2500;
    min_temperature = 1;
    temperature_change = 0.99;
    maxit = 20000;
    stop_time = 60;
}

// zwraca długość trasy, trasa powinna zaczynać i kończyć się 0
int SimulatedAnnealing::pathDistance(vector<int> route_to_calculate)
{
    int path_distance = 0;
    // zliczenie sumy odległości w ścieżce aż do danego wierzchołka
    for (int i = 0; i < number_of_towns - 1; i++)
        path_distance += matrix[route_to_calculate[i]][route_to_calculate[i + 1]];
    return path_distance;
}

// zwraca losowy index poza pierwszym i ostatnim
int SimulatedAnnealing::randomIndex()
{
    return rand() % (number_of_towns - 2) + 1;
}

void SimulatedAnnealing::startSA()
{
    time_t start_time = time(NULL);
    for (int i = 0; i < number_of_towns; i++)
        route.push_back(i);                         // w trasie indexy od 0 do liczby miast
    random_shuffle(route.begin() + 1, route.end()); // losowa trasa zaczynająca się od 0
    route.push_back(0);                             // i kończąca się na 0

    while (true)
    {
        vector<int> temp_route = route; // tymczasowa ścieżka, na której będą przeprowadzane zmiany
        // jeżeli temperatura jest zbyt niska lub przekroczono dozwolony czas to przerwij
        if (temperature < min_temperature || time(NULL) >= start_time + stop_time)
            break;
        for (int i = 0; i < maxit; i++)
        {
            int first_rand_index = randomIndex();
            int second_rand_index = randomIndex();
            while (first_rand_index == second_rand_index) // wylosowane indeksy nie powinny być identyczne
                second_rand_index = randomIndex();

            if (first_rand_index > second_rand_index)
                swap(first_rand_index, second_rand_index);                                              // pierwszy index musi być mniejszy od drugiego
            reverse(temp_route.begin() + first_rand_index + 1, temp_route.begin() + second_rand_index); // odwrócenie wartości pomiędzy wylosowanymi indeksami
            int temp_route_cost = pathDistance(temp_route);
            route_cost = pathDistance(route);
            if (temp_route_cost < route_cost) // jeżeli nowa ścieżka jest lepsza od poprzedniej
                route = temp_route;           // to akceptuj ją jako nową trasę
            else                              // jeżeli znalezione rozwiązanie jest gorsze to zostanie sprawdzony warunek
            {
                if (exp(-(route_cost - temp_route_cost) / temperature) > rand())
                    route = temp_route;
            }
        }
        temperature *= temperature_change; // obniżenie temperatury
    }
    route_cost = pathDistance(route);
}

// wypisuje trasę oraz koszt
void SimulatedAnnealing::printRoute()
{
    for (auto i = 0; i < route.size() - 1; i++)
        cout << route[i] << " -> ";
    cout << route[route.size() - 1] << endl;
    cout << "Cost = " << route_cost << endl;
}
