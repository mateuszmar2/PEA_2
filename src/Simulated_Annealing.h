#ifndef SIMULATED_ANNEALING_H_
#define SIMULATED_ANNEALING_H_

#include <vector>

class SimulatedAnnealing
{
private:
    std::vector<std::vector<int>> matrix;
    int number_of_towns;
    int route_cost;
    double min_temperature;    // minimalna temperatura
    double temperature_change; // jak szybko będzie postępować zmiana temperatury
    double temperature;
    int maxit;     // maksymalna liczba iteracji
    int stop_time; // czas w sekundach po jakim algorytm się zatrzyma
    std::vector<int> route;

public:
    SimulatedAnnealing(std::vector<std::vector<int>> towns);
    int getRouteCost();
    void setStopTime(int stop_time); // ustawia kryterium stopu jako czas wykonania w sekundach
    void setAttributes(double temperature, double min_temperature, double temperature_change, int maxit, int stop_time);
    int pathDistance(std::vector<int> route_to_calculate); // oblicza koszt ścieżki
    int randomIndex();                                     // zwraca losowy indeks miasta
    void startSA();                                        // główna część algorytmu
    void printRoute();                                     // wyświela wynik
};

#endif /* SIMULATED_ANNEALING_H_ */