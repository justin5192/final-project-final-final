#ifndef BRANCHANDBOUND_H
#define BRANCHANDBOUND_H

#include "TSPAlgorithm.h"

class BranchAndBound : public TSPAlgorithm {
public:
    void solve(TSPData& data) override;
    std::vector<int> getSolution() const override;
private:
    std::vector<int> solution;
    int reduceMatrix(std::vector<std::vector<double> >& matrix, int N);
};

#endif
