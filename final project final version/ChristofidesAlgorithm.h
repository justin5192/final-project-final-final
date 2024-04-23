#ifndef CHRISTOFIDESALGORITHM_H
#define CHRISTOFIDESALGORITHM_H

#include "TSPAlgorithm.h"

class ChristofidesAlgorithm : public TSPAlgorithm {
public:
    void solve(TSPData& data) override;
    std::vector<int> getSolution() const override;
private:
    std::vector<int> solution;
    std::vector<int> minimumSpanningTree(const std::vector<std::vector<double> >& adjMatrix, int N);
    std::vector<std::pair<int, int> > minimumWeightPerfectMatching(const std::vector<int>& oddVertices, const std::vector<std::vector<double> >& adjMatrix);
    std::vector<std::vector<int> > createMultiGraph(const std::vector<int>& mst, const std::vector<std::pair<int, int> >& matching, int N);
    std::vector<int> findOddDegreeVertices(const std::vector<int>& mst, int N);
    std::vector<int> findEulerianTour(const std::vector<std::vector<int> >& multigraph, int N);
    std::vector<int> makeHamiltonian(const std::vector<int>& eulerTour);
};

#endif
