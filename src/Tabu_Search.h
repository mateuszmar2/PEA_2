#ifndef TABU_SEARCH_H_
#define TABU_SEARCH_H_

#include <vector>

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

public:
    TabuSearch(std::vector<std::vector<int>> towns);
    int getRouteCost();
    void setStopTime(int stop_time); // ustawia kryterium stopu jako czas wykonania w sekundach
    void setAttributes(int maxit, int stop_time, int tabu_lifetime);
    int pathDistance(std::vector<int> route_to_calculate); // oblicza koszt ścieżki
    int randomIndex();                                     // zwraca losowy indeks miasta
    std::vector<int> newSolution();                        // zwraca najlepszego sąsiada
    void startTS();                                        // główna część algorytmu
    void printRoute();                                     // wyświela wynik
};

#endif /* TABU_SEARCH_H_ */