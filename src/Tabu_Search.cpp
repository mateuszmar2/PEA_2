#include "Tabu_Search.h"

#include <iostream>
#include <algorithm>
#include <ctime>
#include <climits>
#include <chrono>

using namespace std;

TabuSearch::TabuSearch(vector<vector<int>> towns, NeighbourOperation operation, int max_it_without_change, int stop_time, int tabu_lifetime, bool diversification)
{
    matrix = towns;
    number_of_towns = matrix[0].size();
    tabu_list = vector<vector<int>>(number_of_towns, vector<int>(number_of_towns, 0));
    this->operation = operation;
    this->max_it_without_change = max_it_without_change;
    this->stop_time = stop_time;
    this->tabu_lifetime = tabu_lifetime;
    this->diversification = diversification;
}

bool TabuSearch::aspiration(int &current_cost)
{
    return current_cost < route_cost;
}

// tworzy sąsiada wybranego za pomocą danej metody
vector<int> TabuSearch::generateNeighbour(NeighbourOperation o, vector<int> r)
{
    vector<int> current_best_path;
    int current_best_cost = INT_MAX;
    int first_index = 0;
    int second_index = 0;

    for (int i = 1; i < number_of_towns; i++)
    {
        for (int j = 1; j < number_of_towns; j++)
        {
            if (i == j)
                continue;

            vector<int> current_path = r; // tymczasowa ścieżka, na której będą przeprowadzane zmiany
            switch (o)
            {
            case SwapOperation:
                swap(current_path[i], current_path[j]); // zamiana wartości pod danymi indeksami
                break;
            case ReverseOperation:
                if (i < j)
                    reverse(current_path.begin() + i, current_path.begin() + j + 1); // odwrócenie wartości pomiędzy indeksami
                else
                    reverse(current_path.begin() + j, current_path.begin() + i + 1); // odwrócenie wartości pomiędzy indeksami
                break;
            case InsertOperation: // przeniesienie wartości wskazywanej przez pierwszy indeks w miejsce wskazywane przez drugi indeks
                if (i < j)
                    rotate(current_path.begin() + i, current_path.begin() + i + 1, current_path.begin() + j + 1);
                else
                    rotate(current_path.begin() + j, current_path.begin() + i, current_path.begin() + i + 1);
                break;
            }
            int current_cost = pathDistance(current_path);

            if (tabu_list[i][j] != 0)          // jeśli lista tabu zabrania takiej zmiany
                if (!aspiration(current_cost)) // jeżeli kryterium aspiracji nie jest spełnione to kontunuuj pętle
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
    // zaktualizuj liste teabu
    tabu_list[first_index][second_index] = tabu_lifetime;
    if (o != InsertOperation)
        tabu_list[second_index][first_index] = tabu_lifetime;
    return current_best_path;
}

// główna część algorytmu
void TabuSearch::startTS()
{
    chrono::system_clock::time_point start_time = chrono::system_clock::now();
    vector<int> current_best_neighbour;
    vector<int> current_best = randomRoute();
    int current_best_cost = pathDistance(current_best);
    route = current_best;
    route_cost = current_best_cost;
    int it_without_change = 0;

    while (true)
    {
        // jeżeli przekroczono dozwolony czas to przerwij
        int64_t time_diff = chrono::duration_cast<chrono::seconds>(chrono::system_clock::now() - start_time).count();
        if (time_diff >= stop_time)
            break;

        if (diversification && it_without_change > max_it_without_change)
        {
            current_best = randomRoute();
            current_best_cost = pathDistance(current_best);
            for (int i = 0; i < number_of_towns; i++)
                for (int j = 0; j < number_of_towns; j++)
                    tabu_list[i][j] = 0; // wyzeruj listę tabu
            it_without_change = 0;       // oraz liczbę iteracji bez zmiany najlepszej trasy
        }
        else
        {
            current_best_neighbour = generateNeighbour(operation, current_best);
            int current_best_neighbour_cost = pathDistance(current_best_neighbour);
            current_best = current_best_neighbour;
            current_best_cost = current_best_neighbour_cost;
        }

        it_without_change++;

        if (current_best_cost < route_cost) // czy zaakceptowany sąsiad jest lepszy niż dotychczas najlepsza ścieżka
        {
            route = current_best;
            route_cost = current_best_cost;
            it_without_change = 0;
        }

        for (int i = 0; i < number_of_towns; i++)
            for (int j = 0; j < number_of_towns; j++)
                if (tabu_list[i][j] > 0)
                    tabu_list[i][j]--; // dekrementuj każdą większą od 0 wartość w tabu list
    }
}
