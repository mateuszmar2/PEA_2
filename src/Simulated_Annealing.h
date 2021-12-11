#ifndef SIMULATED_ANNEALING_H_
#define SIMULATED_ANNEALING_H_

#include <vector>
#include "Neighbour.h"

class SimulatedAnnealing
{
private:
    std::vector<std::vector<int>> matrix;
    int number_of_towns;
    std::vector<int> route;    // najlepsza ścieżka
    int route_cost;            // jej koszt
    double min_temperature;    // minimalna temperatura
    double temperature_change; // jak szybko będzie postępować zmiana temperatury
    double temperature;        // temperatura początkowa
    int maxit;                 // maksymalna liczba iteracji
    int stop_time;             // czas w sekundach po jakim algorytm się zatrzyma
    NeighbourOperation operation;

public:
    SimulatedAnnealing(std::vector<std::vector<int>> towns, NeighbourOperation operation, double temperature, double min_temperature, double temperature_change, int maxit, int stop_time);
    void calculateTemperature();                                                // wylicza temperaturę na podstawie minimalnej z losowych ścieżek
    int getRouteCost();                                                         // zwraca najlepszą ścieżkę
    std::vector<int> randomRoute();                                             // zwraca losową ścieżkę zaczynającą i kończącą się na 0
    int pathDistance(std::vector<int> route_to_calculate);                      // oblicza koszt ścieżki
    int randomIndex();                                                          // zwraca losowy indeks miasta
    void generateNeighbour(NeighbourOperation o, std::vector<int> &temp_route); // tworzy sąsiada wybranego za pomocą danej metody
    void startSA();                                                             // główna część algorytmu
    void printRoute();                                                          // wyświela wynik
};

#endif /* SIMULATED_ANNEALING_H_ */