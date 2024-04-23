#ifndef TSPDATA_H
#define TSPDATA_H

#include "City.h"
#include <vector>
#include <string>

class TSPData {
public:
    bool loadCitiesWithCoordinate(const std::string& filename, int numCities);
    const std::vector<City>& getCities() const;
    std::vector<std::vector<double> > getAdjacencyMatrix() const;

private:
    std::vector<City> cities;
};

#endif
