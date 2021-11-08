#ifndef SIMULATED_ANNEALING_H_
#define SIMULATED_ANNEALING_H_

#include <vector>

class SimulatedAnnealing
{
private:
    std::vector<std::vector<int>> matrix;
    int number_of_towns;
    int route_cost;
    std::vector<int> route;

public:
    SimulatedAnnealing(std::vector<std::vector<int>> towns);
    int randomIndex(); // zwraca losowy indeks miasta
    void startSA();    // główna część algorytmu
    void printRoute(); // wyświela wynik
};

#endif /* SIMULATED_ANNEALING_H_ */