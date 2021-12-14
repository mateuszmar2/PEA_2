#ifndef SIMULATED_ANNEALING_H_
#define SIMULATED_ANNEALING_H_

#include <vector>
#include "TSP_Algorithm.h"

class SimulatedAnnealing : public TspAlgorithm
{
private:
    double min_temperature;    // minimalna temperatura
    double temperature_change; // jak szybko będzie postępować zmiana temperatury
    double temperature;        // temperatura początkowa
    int maxit;                 // maksymalna liczba iteracji

public:
    SimulatedAnnealing(std::vector<std::vector<int>> towns, NeighbourOperation operation, double temperature, double min_temperature, double temperature_change, int maxit, int stop_time);
    void calculateTemperature();                                                // wylicza temperaturę na podstawie minimalnej z losowych ścieżek
    void generateNeighbour(NeighbourOperation o, std::vector<int> &temp_route); // tworzy sąsiada wybranego za pomocą danej metody
    void startSA();                                                             // główna część algorytmu
};

#endif /* SIMULATED_ANNEALING_H_ */