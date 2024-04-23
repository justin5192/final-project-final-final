#include "GeneticAlgorithm.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <numeric>
#include <unordered_map>
#include <iostream>

#include <unordered_set>
using namespace std;

GeneticAlgorithm::GeneticAlgorithm() {
    srand(time(nullptr));
}

void GeneticAlgorithm::solve(TSPData& data) {
    const int POP_SIZE = 100;
    const int MAX_GENERATIONS = 1000;
    const float MUTATION_RATE = 0.1f;
    const float CROSSOVER_RATE = 0.8f;

    std::vector<std::vector<int> > population(POP_SIZE);
    std::vector<int> bestSolution;
    int bestCost = INT_MAX;

    srand(time(nullptr));

    initializePopulation(population, data.getCities().size());

    for (int generation = 0; generation < MAX_GENERATIONS; ++generation) {
        std::vector<int> fitnesses(POP_SIZE);

        for (int i = 0; i < POP_SIZE; ++i) {
            int cost = evaluateSolution(population[i], data);
            fitnesses[i] = cost;

            if (cost < bestCost) {
                bestCost = cost;
                bestSolution = population[i];
            }
        }

        std::vector<std::vector<int> > newPopulation;
        selectPopulation(population, fitnesses, newPopulation);


        //todo: this is where code slows down tremendously
        for (size_t i = 0; i < newPopulation.size() - 1; i += 2) {

            if (static_cast<float>(rand()) / RAND_MAX < CROSSOVER_RATE) {

                crossover(newPopulation[i], newPopulation[i + 1]);
            }
        }

        for (auto& individual : newPopulation) {
            if (static_cast<float>(rand()) / RAND_MAX < MUTATION_RATE) {
                mutate(individual);
            }
        }

        population = newPopulation;
    }

    solution = bestSolution;
}

std::vector<int> GeneticAlgorithm::getSolution() const {
    return solution;
}

void GeneticAlgorithm::initializePopulation(std::vector<std::vector<int> >& population, int numCities) {
    for (auto& individual : population) {
        individual.resize(numCities);
        std::iota(individual.begin(), individual.end(), 0);
        std::random_shuffle(individual.begin(), individual.end());
    }
}

int GeneticAlgorithm::evaluateSolution(const std::vector<int>& solution, const TSPData& data) {
    int totalCost = 0;
    const std::vector<City>& cities = data.getCities();
    for (size_t i = 0; i < solution.size() - 1; ++i) {
        totalCost += getDistance(cities[solution[i]], cities[solution[i + 1]]);
    }
    totalCost += getDistance(cities[solution.back()], cities[solution.front()]);
    return totalCost;
}

void GeneticAlgorithm::selectPopulation(const std::vector<std::vector<int> >& population, const std::vector<int>& fitnesses, std::vector<std::vector<int> >& newPopulation) {
    newPopulation.resize(population.size());
    float totalFitness = std::accumulate(fitnesses.begin(), fitnesses.end(), 0.0);
    for (size_t i = 0; i < population.size(); ++i) {
        float slice = static_cast<float>(rand()) / RAND_MAX * totalFitness;
        float tempSum = 0.0;
        for (size_t j = 0; j < fitnesses.size(); ++j) {
            tempSum += fitnesses[j];
            if (tempSum >= slice) {
                newPopulation[i] = population[j];
                break;
            }
        }
    }
}

void GeneticAlgorithm::crossover(std::vector<int>& parent1, std::vector<int>& parent2) {
    int size = parent1.size();
    int crossoverPoint1 = rand() % size;
    int crossoverPoint2 = rand() % size;

    if (crossoverPoint1 > crossoverPoint2) {
        std::swap(crossoverPoint1, crossoverPoint2);
    }

    std::vector<int> child1 = parent1;
    std::vector<int> child2 = parent2;

    std::unordered_map<int, int> mapping1to2, mapping2to1;

    for (int i = crossoverPoint1; i <= crossoverPoint2; ++i) {
        child1[i] = parent2[i];
        child2[i] = parent1[i];
        mapping1to2[parent1[i]] = parent2[i];
        mapping2to1[parent2[i]] = parent1[i];
    }

    for (int i = 0; i < size; ++i) {
        if ((i < crossoverPoint1) || (i > crossoverPoint2)) {
            int originalValue = child1[i];
            while (std::find(child1.begin() + crossoverPoint1, child1.begin() + crossoverPoint2 + 1, originalValue) != child1.begin() + crossoverPoint2 + 1) {
                originalValue = mapping2to1[originalValue];
            }
            child1[i] = originalValue;

            originalValue = child2[i];
            while (std::find(child2.begin() + crossoverPoint1, child2.begin() + crossoverPoint2 + 1, originalValue) != child2.begin() + crossoverPoint2 + 1) {
                originalValue = mapping1to2[originalValue];
            }
            child2[i] = originalValue;
        }
    }

    parent1 = child1;
    parent2 = child2;
}


void GeneticAlgorithm::mutate(std::vector<int>& individual) {
    int index1 = rand() % individual.size();
    int index2 = rand() % individual.size();
    std::swap(individual[index1], individual[index2]);
}
