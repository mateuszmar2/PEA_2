#include "Simulated_Annealing.h"

#include <iostream>
#include <algorithm>
#include <ctime>
#include <math.h>
#include <chrono>
#include <climits>

using namespace std;

SimulatedAnnealing::SimulatedAnnealing(vector<vector<int>> towns, NeighbourOperation operation, double temperature, double min_temperature, double temperature_change, int maxit, int stop_time)
{
    matrix = towns;
    number_of_towns = matrix[0].size();
    this->operation = operation;
    this->temperature = temperature;
    this->min_temperature = min_temperature;
    this->temperature_change = temperature_change;
    this->maxit = maxit;
    this->stop_time = stop_time;
}
// oblicza temperaturę na podstawie wielkości problemu
void SimulatedAnnealing::calculateTemperature()
{
    for (int i = 0; i < number_of_towns; i++)
    {
        vector<int> random_route = randomRoute();
        int cost = pathDistance(random_route);
        if (cost < route_cost)
        {
            route_cost = cost;
            route = random_route;
        }
    }
    this->temperature = route_cost;
    cout << "temperature = " << temperature << endl;
}

// tworzy sąsiada za pomocą wybranej metody
void SimulatedAnnealing::generateNeighbour(NeighbourOperation o, vector<int> &route)
{
    int first_rand_index = randomIndex();
    int second_rand_index = randomIndex();
    while (first_rand_index == second_rand_index) // wylosowane indeksy nie nogą być identyczne
        second_rand_index = randomIndex();

    switch (o)
    {
    case SwapOperation:
        swap(route[first_rand_index], route[second_rand_index]); // zamiana wartości pod wylosowanymi indeksami
        break;
    case ReverseOperation:
        if (first_rand_index > second_rand_index)
            swap(first_rand_index, second_rand_index);                                    // pierwszy index musi być mniejszy od drugiego
        reverse(route.begin() + first_rand_index, route.begin() + second_rand_index + 1); // odwrócenie wartości pomiędzy wylosowanymi indeksami
        break;
    case InsertOperation: // przeniesienie wartości wskazywanej przez pierwszy indeks w miejsce wskazywane przez drugi indeks
        if (first_rand_index < second_rand_index)
            rotate(route.begin() + first_rand_index, route.begin() + first_rand_index + 1, route.begin() + second_rand_index + 1);
        else
            rotate(route.begin() + second_rand_index, route.begin() + first_rand_index, route.begin() + first_rand_index + 1);
        break;
    }
}

// główna część algorytmu
void SimulatedAnnealing::startSA()
{
    chrono::system_clock::time_point start_time = chrono::system_clock::now();
    route = randomRoute(); // route to globalnie najlepsza ścieżka
    route_cost = pathDistance(route);
    if (temperature == 0)
        calculateTemperature();
    vector<int> current_best = route;
    int current_best_cost = route_cost;

    while (true)
    {
        // jeżeli temperatura jest zbyt niska lub przekroczono dozwolony czas to przerwij
        int64_t time_diff = chrono::duration_cast<chrono::seconds>(chrono::system_clock::now() - start_time).count();
        if (temperature < min_temperature || time_diff >= stop_time)
            break;

        for (int i = 0; i < maxit; i++) // dopóki nie przekroczono dozwolonej liczby iteracji
        {
            vector<int> current_best_neighbour = current_best; // tymczasowa ścieżka, na której będą przeprowadzane zmiany
            generateNeighbour(operation, current_best_neighbour);
            int current_best_neighbour_cost = pathDistance(current_best_neighbour);
            if (current_best_neighbour_cost >= current_best_cost) // jeżeli nowa ścieżka jest gorsza od poprzedniej
            {
                double delta = current_best_neighbour_cost - current_best_cost;
                if (exp(-delta / temperature) < (double)rand() / RAND_MAX) // jeżeli znalezione rozwiązanie jest gorsze to sąsiad jest odrzucany
                    continue;
            }
            current_best = current_best_neighbour; // akceptuj sąsiada
            current_best_cost = current_best_neighbour_cost;

            if (current_best_cost < route_cost) // czy zaakceptowany sąsiad jest lepszy niż dotychczas najlepsza
            {
                route = current_best;
                route_cost = current_best_cost;
            }
        }
        temperature *= temperature_change; // obniżenie temperatury
    }
}
