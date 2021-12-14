#ifndef TABU_SEARCH_H_
#define TABU_SEARCH_H_

#include <vector>
#include "TSP_Algorithm.h"

class TabuSearch : public TspAlgorithm
{
private:
    int max_it_without_change; // maksymalna liczba iteracji
    int tabu_lifetime; // ilość iteracji, po których będzie można wykonać ten ruch
    bool diversification;
    std::vector<std::vector<int>> tabu_list;

public:
    TabuSearch(std::vector<std::vector<int>> towns, NeighbourOperation operation, int max_it_without_change, int stop_time, int tabu_lifetime, bool diversification);
    bool aspiration(int &current_cost);                                           // funkcja sprawdzająca kryterium aspiracji
    std::vector<int> generateNeighbour(NeighbourOperation o, std::vector<int> r); // tworzy sąsiada wybranego za pomocą danej metody
    void startTS();                                                               // główna część algorytmu
};

#endif /* TABU_SEARCH_H_ */