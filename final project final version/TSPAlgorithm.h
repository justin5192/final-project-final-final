#ifndef TSPALGORITHM_H
#define TSPALGORITHM_H

#include "TSPData.h"
#include <vector>

class TSPAlgorithm {
public:
    virtual void solve(TSPData& data) = 0;
    virtual std::vector<int> getSolution() const = 0;
    virtual ~TSPAlgorithm() {}
};

#endif
