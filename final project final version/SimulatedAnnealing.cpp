#include "SimulatedAnnealing.h"
#include <numeric>
#include <cmath>
#include <cstdlib>
#include <ctime>

SimulatedAnnealing::SimulatedAnnealing() {
    srand(time(nullptr));
}

void SimulatedAnnealing::solve(TSPData& data) {
    double temperature = 10000;
    double coolingRate = 0.999;
    double absoluteTemperature = 1e-10;

    std::vector<int> currentSolution = generateInitialSolution(data.getCities().size());
    std::vector<int> bestSolution = currentSolution;
    int currentCost = evaluateSolution(currentSolution, data);
    int bestCost = currentCost;

    while (temperature > absoluteTemperature) {
        std::vector<int> newSolution = getNeighbour(currentSolution);
        int newCost = evaluateSolution(newSolution, data);

        if (acceptanceProbability(currentCost, newCost, temperature) > static_cast<double>(rand()) / RAND_MAX) {
            currentSolution = newSolution;
            currentCost = newCost;

            if (currentCost < bestCost) {
                bestSolution = currentSolution;
                bestCost = currentCost;
            }
        }

        temperature *= coolingRate;
    }

    solution = bestSolution;
}

std::vector<int> SimulatedAnnealing::getSolution() const {
    return solution;
}

std::vector<int> SimulatedAnnealing::generateInitialSolution(int numCities) {
    std::vector<int> solution(numCities);
    std::iota(solution.begin(), solution.end(), 0);
    std::random_shuffle(solution.begin(), solution.end());
    return solution;
}

std::vector<int> SimulatedAnnealing::getNeighbour(std::vector<int>& currentSolution) {
    std::vector<int> newSolution = currentSolution;
    int index1 = rand() % newSolution.size();
    int index2 = (index1 + 1 + rand() % (newSolution.size() - 1)) % newSolution.size();
    std::swap(newSolution[index1], newSolution[index2]);
    return newSolution;
}

int SimulatedAnnealing::evaluateSolution(const std::vector<int>& solution, const TSPData& data) {
    int totalCost = 0;
    const std::vector<City>& cities = data.getCities();
    for (size_t i = 0; i < solution.size() - 1; ++i) {
        totalCost += getDistance(cities[solution[i]], cities[solution[i + 1]]);
    }
    totalCost += getDistance(cities[solution.back()], cities[solution.front()]);
    return totalCost;
}

double SimulatedAnnealing::acceptanceProbability(int energy, int newEnergy, double temperature) {
    if (newEnergy < energy) {
        return 1.0;
    }
    return exp((energy - newEnergy) / temperature);
}
