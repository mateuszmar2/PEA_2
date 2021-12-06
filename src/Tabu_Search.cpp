#include "Tabu_Search.h"

#include <iostream>
#include <algorithm>
#include <ctime>
#include <climits>

using namespace std;

int TabuSearch::getRouteCost()
{
    return route_cost;
}

TabuSearch::TabuSearch(vector<vector<int>> towns)
{
    srand(time(NULL));
    matrix = towns;
    number_of_towns = matrix[0].size();
    tabu_list = vector<vector<int>>(number_of_towns, vector<int>(number_of_towns, 0));
}

void TabuSearch::setAttributes(int maxit, int stop_time, int tabu_lifetime)
{
    this->maxit = maxit;
    this->stop_time = stop_time;
    this->tabu_lifetime = tabu_lifetime;
}

// zwraca długość trasy, trasa powinna zaczynać i kończyć się 0
int TabuSearch::pathDistance(vector<int> route_to_calculate)
{
    int path_distance = 0;
    // zliczenie sumy odległości w ścieżce aż do danego wierzchołka
    for (int i = 0; i < number_of_towns; i++)
        path_distance += matrix[route_to_calculate[i]][route_to_calculate[i + 1]];
    return path_distance;
}

// zwraca losowy index poza pierwszym i ostatnim
int TabuSearch::randomIndex()
{
    return rand() % (number_of_towns - 2) + 1;
}

// zwraca najlepszego sąsiada
vector<int> TabuSearch::newSolution()
{
    vector<int> temp_route = route; // tymczasowa ścieżka, na której będą przeprowadzane zmiany
    int temp_route_cost = pathDistance(temp_route);
    vector<int> current_best_path;
    int current_best_cost = INT_MAX;
    int first_index = 0;
    int second_index = 0;
    for (int i = 0; i < number_of_towns; i++)
    {
        for (int j = 0; j < number_of_towns; j++)
        {
            if (tabu_list[i][j] == 0) // jeśli lista tabu nie zabrania takiej zmiany
            {
                swap(temp_route[i], temp_route[j]);
                int temp_route_cost = pathDistance(temp_route);

                if (temp_route_cost < route_cost) // jeżeli nowa ścieżka jest lepsza od poprzedniej
                {
                    current_best_path = temp_route; // to akceptuj ją jako nową trasę
                    current_best_cost = temp_route_cost;
                    first_index = i; // zapamiętaj indeksy, potrzebne do listy tabu
                    second_index = j;
                }
                swap(temp_route[i], temp_route[j]);
            }
        }
    }
    tabu_list[first_index][second_index] = tabu_lifetime;
    // int first_rand_index = randomIndex();
    // int second_rand_index = randomIndex();
    // while (first_rand_index == second_rand_index) // wylosowane indeksy nie powinny być identyczne
    //     second_rand_index = randomIndex();

    // if (first_rand_index > second_rand_index)
    //     swap(first_rand_index, second_rand_index); // pierwszy index musi być mniejszy od drugiego
    // // reverse(temp_route.begin() + first_rand_index + 1, temp_route.begin() + second_rand_index); // odwrócenie wartości pomiędzy wylosowanymi indeksami
    // swap(temp_route[first_rand_index], temp_route[second_rand_index]);
    return temp_route;
}

// główna część algorytmu
void TabuSearch::startTS()
{
    time_t start_time = time(NULL);
    for (int i = 0; i < number_of_towns; i++)
        route.push_back(i);                         // w trasie indexy od 0 do liczby miast
    random_shuffle(route.begin() + 1, route.end()); // losowa trasa zaczynająca się od 0
    route.push_back(0);                             // i kończąca się na 0
    route_cost = pathDistance(route);

    while (true)
    {
        // jeżeli przekroczono dozwolony czas to przerwij
        if (time(NULL) >= start_time + stop_time)
            break;
        for (int i = 0; i < maxit; i++)
        {
            vector<int> temp_route = newSolution();
            int temp_route_cost = pathDistance(temp_route);
            if (temp_route_cost < route_cost) // jeżeli nowa ścieżka jest lepsza od poprzedniej
            {
                route = temp_route; // to akceptuj ją jako nową trasę
                route_cost = temp_route_cost;
            }
            for (int i = 0; i < number_of_towns; i++)
                for (int j = 0; j < number_of_towns; j++)
                    if (tabu_list[i][j] > 0)
                        tabu_list[i][j]--; // dekrementuj każdą większą od 0 wartość w tabu list
        }
    }
}

// wypisuje trasę oraz koszt
void TabuSearch::printRoute()
{
    // for (auto i = 0; i < route.size() - 1; i++)
    //     cout << route[i] << " -> ";
    // cout << route[route.size() - 1] << endl;
    cout << "Cost = " << route_cost << endl;
}
