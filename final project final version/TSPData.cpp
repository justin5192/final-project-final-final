#include "TSPData.h"
#include "City.h"
#include <fstream>
#include <iostream>
using namespace std;

bool TSPData::loadCitiesWithCoordinate(const std::string& filename, int numCities) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    City city;
    int count = 0;
    while (file >> city.x_coordinate >> city.y_coordinate) {
        city.cityID = count;
        cities.push_back(city);
        if (++count == numCities) break;
    }

    file.close();
    return true;
}

const std::vector<City>& TSPData::getCities() const {
    return cities;
}

std::vector<std::vector<double> > TSPData::getAdjacencyMatrix() const {
    int n = cities.size();
    cout << cities.size() << endl;
    std::vector<std::vector<double> > matrix(n, std::vector<double>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            matrix[i][j] = getDistance(cities[i], cities[j]);
        }
    }
    return matrix;
}
