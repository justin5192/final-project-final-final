#ifndef CITY_H
#define CITY_H

#include <algorithm>
#include <vector>

struct City {
    int cityID;
    double x_coordinate;
    double y_coordinate;
};

double getDistance(const City& city1, const City& city2);
double getTourDistance(const std::vector<int> tour, const std::vector<City> cities);

#endif
