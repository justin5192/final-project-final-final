#include "TSPData.h"
#include "GeneticAlgorithm.h"
#include "SimulatedAnnealing.h"
#include "BranchAndBound.h"
#include "ChristofidesAlgorithm.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

int main() {

    string filename = "random_pairs_small_range.txt";
    int numCities = 0;

    TSPData tspData;
    if (!tspData.loadCitiesWithCoordinate(filename, numCities)) {
        std::cerr << "Failed to load cities from file." << std::endl;
        return 1;
    }

    vector<City> cities = tspData.getCities();

    vector<int> tour_genetic;
    vector<int> tour_annealing;
    vector<int> tour_branch;
    vector<int> tour_christofides;

    GeneticAlgorithm genetic;
    genetic.solve(tspData); // TODO: code freezes here
    tour_genetic = genetic.getSolution();

    // Code for reading text based on code in GeeksForGeeks article
    // https://www.geeksforgeeks.org/how-to-read-a-local-text-file-using-javascript/

    std::fstream fout_genetic;
    fout_genetic << std::fixed << std::setprecision(6);
    fout_genetic.open("genetic_output.csv",std::ios::out);
    fout_genetic << "city_id" << "," << "x_value" << "," << "y_value" << "\n";
    for (unsigned int i = 0; i < tour_genetic.size(); i++) {
        fout_genetic << cities[tour_genetic[i]].cityID << ","
                     << cities[tour_genetic[i]].x_coordinate << ","
                     << cities[tour_genetic[i]].y_coordinate << "\n";
    }

    SimulatedAnnealing simulatedAnnealing;
    simulatedAnnealing.solve(tspData);
    tour_annealing = simulatedAnnealing.getSolution();

    std::fstream fout_annealing;
    fout_annealing << std::fixed << std::setprecision(6);
    fout_annealing.open("annealing_output.csv", std::ios::out);
    fout_annealing << "city_id" << "," << "x_value" << "," << "y_value" << "\n";
    for (unsigned int i = 0; i < tour_annealing.size(); i++) {
        fout_annealing << cities[tour_annealing[i]].cityID << ","
                       << cities[tour_annealing[i]].x_coordinate << ","
                       << cities[tour_annealing[i]].y_coordinate << "\n";
    }

    BranchAndBound branchAndBound;
    branchAndBound.solve(tspData);
    tour_branch = branchAndBound.getSolution();

    std::fstream fout_branch;
    fout_branch << std::fixed << std::setprecision(6);
    fout_branch.open("branch_output.csv", std::ios::out);
    fout_branch << "city_id" << "," << "x_value" << "," << "y_value" << "\n";
    for (unsigned int i = 0; i < tour_branch.size(); i++) {
        fout_branch << cities[tour_branch[i]].cityID << ","
                    << cities[tour_branch[i]].x_coordinate << ","
                    << cities[tour_branch[i]].y_coordinate << "\n";
    }

    ChristofidesAlgorithm christofides;
    christofides.solve(tspData);
    tour_christofides = christofides.getSolution();

    std::fstream fout_christofides;
    fout_christofides << std::fixed << std::setprecision(6);
    fout_christofides.open("christofides_output.csv", std::ios::out);
    fout_christofides << "city_id" << "," << "x_value" << "," << "y_value" << "\n";
    for (unsigned int i = 0; i < tour_christofides.size(); i++) {
        fout_christofides << cities[tour_christofides[i]].cityID << ","
                          << cities[tour_christofides[i]].x_coordinate << ","
                          << cities[tour_christofides[i]].y_coordinate << "\n";
    }
    std::cout << "tour genetic: ";
    for (int city : tour_genetic) {
        std::cout << city << " ";
    }
    std::cout << std::endl;
    std::cout << "distance: " << getTourDistance(tour_genetic, tspData.getCities()) << std::endl;
    cout << endl;

    std::cout << "tour annealing: ";
    for (int city : tour_annealing) {
        std::cout << city << " ";
    }
    std::cout << std::endl;
    std::cout << "distance: " << getTourDistance(tour_annealing, tspData.getCities()) << std::endl;
    cout << endl;

    std::cout << "tour branch: ";
    for (int city : tour_branch) {
        std::cout << city << " ";
    }
    std::cout << std::endl;
    std::cout << "distance: " << getTourDistance(tour_branch, tspData.getCities()) << std::endl;
    cout << endl;

    std::cout << "tour christofides: ";
    for (int city : tour_christofides) {
        std::cout << city << " ";
    }
    std::cout << std::endl;
    std::cout << "distance: " << getTourDistance(tour_christofides, tspData.getCities()) << std::endl;
    cout << endl;

    return 0;
}
