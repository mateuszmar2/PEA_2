#ifndef TABU_SEARCH_H_
#define TABU_SEARCH_H_

#include <vector>
#include "Neighbour.h"

class TabuSearch
{
private:
    std::vector<std::vector<int>> matrix;
    int number_of_towns;
    int route_cost;
    int maxit;         // maksymalna liczba iteracji
    int stop_time;     // czas w sekundach po jakim algorytm się zatrzyma
    int tabu_lifetime; // ilość iteracji, po których będzie można wykonać ten ruch
    std::vector<int> route;
    std::vector<std::vector<int>> tabu_list;
    NeighbourOperation operation;

public:
    TabuSearch(std::vector<std::vector<int>> towns, NeighbourOperation operation, int maxit, int stop_time, int tabu_lifetime);
    int getRouteCost();
    std::vector<int> randomRoute();                                                   // zwraca losową ścieżkę zaczynającą i kończącą się na 0
    int pathDistance(std::vector<int> route_to_calculate);                            // oblicza koszt ścieżki
    int randomIndex();                                                                // zwraca losowy indeks miasta
    bool aspiration(int x, int y, int current_cost);                                  // funkcja sprawdzająca kryterium aspiracji
    std::vector<int> generateNeighbour(NeighbourOperation o, std::vector<int> route); // tworzy sąsiada wybranego za pomocą danej metody
    std::vector<int> newSolution();                                                   // zwraca najlepszego sąsiada
    void startTS();                                                                   // główna część algorytmu
    void printRoute();                                                                // wyświela wynik
};

#endif /* TABU_SEARCH_H_ */