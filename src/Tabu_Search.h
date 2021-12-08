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
    int max_it_without_change; // maksymalna liczba iteracji
    int stop_time;             // czas w sekundach po jakim algorytm się zatrzyma
    int tabu_lifetime;         // ilość iteracji, po których będzie można wykonać ten ruch
    bool diversification;
    std::vector<int> route;
    std::vector<std::vector<int>> tabu_list;
    NeighbourOperation operation;

public:
    TabuSearch(std::vector<std::vector<int>> towns, NeighbourOperation operation, int max_it_without_change, int stop_time, int tabu_lifetime, bool diversification);
    int getRouteCost();
    std::vector<int> randomRoute();                                               // zwraca losową ścieżkę zaczynającą i kończącą się na 0
    int pathDistance(std::vector<int> route_to_calculate);                        // oblicza koszt ścieżki
    int randomIndex();                                                            // zwraca losowy indeks miasta
    bool aspiration(int &current_cost);                                           // funkcja sprawdzająca kryterium aspiracji
    std::vector<int> generateNeighbour(NeighbourOperation o, std::vector<int> r); // tworzy sąsiada wybranego za pomocą danej metody
    std::vector<int> newSolution();                                               // zwraca najlepszego sąsiada
    void startTS();                                                               // główna część algorytmu
    void printRoute();                                                            // wyświela wynik
};

#endif /* TABU_SEARCH_H_ */