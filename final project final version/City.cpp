#include "City.h"
#include "cmath"

double getDistance(const City& city1, const City& city2) {
    return std::sqrt(std::pow(city1.x_coordinate - city2.x_coordinate, 2) + std::pow(city1.y_coordinate - city2.y_coordinate, 2));
}

double getTourDistance(const std::vector<int> tour, const std::vector<City> cities) {
    double distance = 0;
    for (int i = 0; i < tour.size() - 1; ++i) {
        distance += getDistance(cities[tour[i]], cities[tour[i + 1]]);
    }
    distance += getDistance(cities[tour.back()], cities[tour[0]]);
    return distance;
}
