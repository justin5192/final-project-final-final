#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "TSPAlgorithm.h"

class GeneticAlgorithm : public TSPAlgorithm {
public:
    GeneticAlgorithm();
    void solve(TSPData& data) override;
    std::vector<int> getSolution() const override;
private:
    std::vector<int> solution;
    void initializePopulation(std::vector<std::vector<int> >& population, int numCities);
    int evaluateSolution(const std::vector<int>& solution, const TSPData& data);
    void selectPopulation(const std::vector<std::vector<int> >& population, const std::vector<int>& fitnesses, std::vector<std::vector<int> >& newPopulation);
    void crossover(std::vector<int>& parent1, std::vector<int>& parent2);
    void mutate(std::vector<int>& individual);
};

#endif
