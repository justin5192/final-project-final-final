#include "ChristofidesAlgorithm.h"
#include <set>
#include <utility>
#include <vector>
#include <list>
#include <limits>

void ChristofidesAlgorithm::solve(TSPData& data) {
    int N = data.getCities().size();
    std::vector<std::vector<double> > adjMatrix = data.getAdjacencyMatrix();

    std::vector<int> mst = minimumSpanningTree(adjMatrix, N);
    std::vector<int> oddVertices = findOddDegreeVertices(mst, N);
    std::vector<std::pair<int, int> > minWeightMatching = minimumWeightPerfectMatching(oddVertices, adjMatrix);
    std::vector<std::vector<int> > multigraph = createMultiGraph(mst, minWeightMatching, N);
    std::vector<int> eulerTour = findEulerianTour(multigraph, N);
    solution = makeHamiltonian(eulerTour);
}

std::vector<int> ChristofidesAlgorithm::minimumSpanningTree(const std::vector<std::vector<double> >& adjMatrix, int N) {
    std::vector<int> parent(N, -1);
    std::vector<int> key(N, std::numeric_limits<int>::max());
    std::vector<bool> inMST(N, false);
    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < N - 1; count++) {
        int u = -1;
        int min = std::numeric_limits<int>::max();

        for (int v = 0; v < N; v++)
            if (!inMST[v] && key[v] < min)
                min = key[v], u = v;

        inMST[u] = true;

        for (int v = 0; v < N; v++)
            if (adjMatrix[u][v] && !inMST[v] && adjMatrix[u][v] < key[v])
                parent[v] = u, key[v] = adjMatrix[u][v];
    }
    return parent;
}

std::vector<int> ChristofidesAlgorithm::findOddDegreeVertices(const std::vector<int>& mst, int N) {
    std::vector<int> degree(N, 0);
    for (int i = 0; i < N; i++)
        if (mst[i] != -1)
            degree[i]++, degree[mst[i]]++;

    std::vector<int> oddVertices;
    for (int i = 0; i < N; i++)
        if (degree[i] % 2 != 0)
            oddVertices.push_back(i);

    return oddVertices;
}

std::vector<std::pair<int, int> > ChristofidesAlgorithm::minimumWeightPerfectMatching(const std::vector<int>& oddVertices, const std::vector<std::vector<double> >& adjMatrix) {
    std::set<std::pair<int, int> > matching;
    std::vector<bool> visited(oddVertices.size(), false);

    for (int i = 0; i < oddVertices.size(); i++) {
        if (!visited[i]) {
            int closest = -1, length = std::numeric_limits<int>::max();
            for (int j = 0; j < oddVertices.size(); j++) {
                if (i != j && !visited[j] && adjMatrix[oddVertices[i]][oddVertices[j]] < length) {
                    closest = j;
                    length = adjMatrix[oddVertices[i]][oddVertices[j]];
                }
            }
            matching.insert(std::make_pair(oddVertices[i], oddVertices[closest]));
            visited[i] = true;
            visited[closest] = true;
        }
    }
    return std::vector<std::pair<int, int> >(matching.begin(), matching.end());
}

std::vector<std::vector<int> > ChristofidesAlgorithm::createMultiGraph(const std::vector<int>& mst, const std::vector<std::pair<int, int> >& matching, int N) {
    std::vector<std::vector<int> > multigraph(N, std::vector<int>(N, 0));
    for (int i = 1; i < N; i++) {
        multigraph[i][mst[i]]++;
        multigraph[mst[i]][i]++;
    }
    for (auto& edge : matching) {
        multigraph[edge.first][edge.second]++;
        multigraph[edge.second][edge.first]++;
    }
    return multigraph;
}

std::vector<int> ChristofidesAlgorithm::findEulerianTour(const std::vector<std::vector<int> >& multigraph, int N) {
    std::vector<int> tour;
    std::list<int> stack;
    std::vector<std::vector<int> > graph = multigraph; // 创建一个可修改的副本
    std::vector<std::vector<bool> > used(N, std::vector<bool>(N, false));
    stack.push_back(0);

    while (!stack.empty()) {
        int v = stack.back();
        bool found = false;
        for (int i = 0; i < N; i++) {
            if (graph[v][i] > 0 && !used[v][i]) {
                stack.push_back(i);
                used[v][i] = used[i][v] = true;
                graph[v][i]--;
                graph[i][v]--;
                found = true;
                break;
            }
        }
        if (!found) {
            stack.pop_back();
            tour.push_back(v);
        }
    }
    std::reverse(tour.begin(), tour.end());
    return tour;
}

std::vector<int> ChristofidesAlgorithm::makeHamiltonian(const std::vector<int>& eulerTour) {
    std::vector<int> path;
    std::set<int> visited;
    for (int v : eulerTour) {
        if (visited.find(v) == visited.end()) {
            path.push_back(v);
            visited.insert(v);
        }
    }
    path.push_back(path[0]);
    return path;
}

std::vector<int> ChristofidesAlgorithm::getSolution() const {
    std::vector<int> res = solution;
    res.pop_back();
    return res;
}
