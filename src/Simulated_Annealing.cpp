#include "Simulated_Annealing.h"

#include <iostream>
// #include <stdlib.h>
#include <algorithm>

using namespace std;

SimulatedAnnealing::SimulatedAnnealing(vector<vector<int>> towns)
{
    matrix = towns;
    number_of_towns = matrix[0].size();
}

int SimulatedAnnealing::randomIndex()
{
    return rand() % (number_of_towns - 2) + 1; // zwraca losowy index poza pierwszym i ostatnim
}

void SimulatedAnnealing::startSA()
{
    for (int i = 0; i < number_of_towns; i++)
        route.push_back(i);                         // w trasie indexy od 0 do liczby miast
    random_shuffle(route.begin() + 1, route.end()); // losowa trasa zaczynająca się od 0
    route.push_back(0);                             // i kończąca się na 0
    int first_rand_index = randomIndex();
    int second_rand_index = randomIndex();
    if (first_rand_index > second_rand_index)
        swap(first_rand_index, second_rand_index);                  // pierwszy index ma być mniejszy od drugiego
    reverse(route[first_rand_index + 1], route[second_rand_index]); // odwrócenie wartości pomiędzy wylosowanymi indeksami
}

void SimulatedAnnealing::printRoute()
{
    for (auto i = 0; i < route.size() - 1; i++)
        cout << route[i] << " -> ";
    cout << route[route.size() - 1] << endl;
    cout << "Cost = " << route_cost << endl;
}