#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H

#include "TSPAlgorithm.h"

class SimulatedAnnealing : public TSPAlgorithm {
public:
    SimulatedAnnealing();
    void solve(TSPData& data) override;
    std::vector<int> getSolution() const override;
private:
    std::vector<int> solution;
    std::vector<int> generateInitialSolution(int numCities);
    std::vector<int> getNeighbour(std::vector<int>& currentSolution);
    int evaluateSolution(const std::vector<int>& solution, const TSPData& data);
    double acceptanceProbability(int energy, int newEnergy, double temperature);
};

#endif
