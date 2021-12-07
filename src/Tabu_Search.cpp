#include "Tabu_Search.h"

#include <iostream>
#include <algorithm>
#include <ctime>
#include <climits>

using namespace std;

TabuSearch::TabuSearch(vector<vector<int>> towns, NeighbourOperation operation, int maxit, int stop_time, int tabu_lifetime)
{
    srand(time(NULL));
    matrix = towns;
    number_of_towns = matrix[0].size();
    tabu_list = vector<vector<int>>(number_of_towns, vector<int>(number_of_towns, 0));
    this->operation = operation;
    this->maxit = maxit;
    this->stop_time = stop_time;
    this->tabu_lifetime = tabu_lifetime;
}

int TabuSearch::getRouteCost()
{
    return route_cost;
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

// zwraca losową ścieżkę zaczynającą i kończącą się na 0
vector<int> TabuSearch::randomRoute()
{
    vector<int> temp;
    for (int i = 0; i < number_of_towns; i++)
        temp.push_back(i);                        // w trasie indexy od 0 do liczby miast
    random_shuffle(temp.begin() + 1, temp.end()); // losowa trasa zaczynająca się od 0
    temp.push_back(0);                            // i kończąca się na 0
    return temp;
}

bool TabuSearch::aspiration(int x, int y, int current_cost)
{
    if (current_cost < route_cost)
        return true;
    return false;
}

// tworzy sąsiada wybranego za pomocą danej metody
vector<int> TabuSearch::generateNeighbour(NeighbourOperation o, vector<int> route)
{
    vector<int> current_best_path;
    int current_best_cost = INT_MAX;
    int first_index = 0;
    int second_index = 0;

    for (int i = 1; i < number_of_towns - 1; i++)
    {
        for (int j = 1; j < number_of_towns - 1; j++)
        {
            vector<int> current_path = route; // tymczasowa ścieżka, na której będą przeprowadzane zmiany
            int first_index = i;
            int second_index = j;
            switch (o)
            {
            case SwapOperation:
                swap(current_path[first_index], current_path[second_index]);
                break;
            case ReverseOperation:
                if (first_index > second_index)
                    swap(first_index, second_index);                                                  // pierwszy index musi być mniejszy od drugiego
                reverse(current_path.begin() + first_index, current_path.begin() + second_index + 1); // odwrócenie wartości pomiędzy wylosowanymi indeksami
                break;
            case InsertOperation:
                if (first_index > second_index)
                    swap(first_index, second_index); // pierwszy index musi być mniejszy od drugiego

                rotate(current_path.begin() + first_index, current_path.begin() + first_index + 1, current_path.begin() + second_index + 1); // wstawienie wartości za wylosowanym indeksem
                break;
            }
            int current_cost = pathDistance(current_path);

            if (tabu_list[i][j] != 0)                // jeśli lista tabu zabrania takiej zmiany
                if (!aspiration(i, j, current_cost)) // jeżeli kryterium aspiracji nie jest spełnione zakazu to kontunuuj pętle
                    continue;

            // jeżeli tabu nie zabrania lub kryterium aspiracji zostało spełnione to można wziąć pod uwagę dane rozwiązanie
            if (current_cost < current_best_cost) // jeżeli nowa ścieżka jest lepsza od poprzedniej
            {
                current_best_path = current_path; // to akceptuj ją jako nową trasę
                current_best_cost = current_cost;
                first_index = i; // zapamiętaj indeksy, potrzebne do listy tabu
                second_index = j;
            }
        }
    }
    tabu_list[first_index][second_index] = tabu_lifetime;
    tabu_list[second_index][first_index] = tabu_lifetime;
    return current_best_path;
}

// główna część algorytmu
void TabuSearch::startTS()
{
    time_t start_time = time(NULL);
    vector<int> current_best = randomRoute();
    int current_best_cost = pathDistance(current_best);
    route = current_best;
    route_cost = current_best_cost;

    // while (true)
    // {
    for (int i = 0; i < maxit; i++) // dopóki nie przekroczono dozwolonej liczby iteracji
    {
        // jeżeli przekroczono dozwolony czas to przerwij
        if (time(NULL) >= start_time + stop_time)
            break;
        vector<int> current_best_neighbour = generateNeighbour(operation, current_best);
        int current_best_neighbour_cost = pathDistance(current_best_neighbour);
        if (current_best_neighbour_cost < current_best_cost) // jeżeli nowa ścieżka jest lepsza od poprzedniej najlepszej
        {
            current_best = current_best_neighbour; // to akceptuj ją jako nową trasę
            current_best_cost = current_best_neighbour_cost;
        }
        if (current_best_cost < route_cost) // czy zaakceptowany sąsiad jest lepszy niż dotychczas najlepsza ścieżka
        {
            route = current_best;
            route_cost = current_best_cost;
        }
        // TODO tutaj chyba lepiej dodawać elementy do listy tabu
        for (int i = 0; i < number_of_towns; i++)
            for (int j = 0; j < number_of_towns; j++)
                if (tabu_list[i][j] > 0)
                    tabu_list[i][j]--; // dekrementuj każdą większą od 0 wartość w tabu list
    }
    // }
}

// wypisuje trasę oraz koszt
void TabuSearch::printRoute()
{
    for (auto i = 0; i < route.size() - 1; i++)
        cout << route[i] << " -> ";
    cout << route[route.size() - 1] << endl;
    cout << "Cost = " << route_cost << endl;
}
