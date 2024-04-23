#include "BranchAndBound.h"
#include <limits>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

struct Node {
    std::vector<int> path;
    int reducedMatrixSize;
    std::vector<std::vector<double> > reducedMatrix;
    int cost;
    int vertex;
    int level;
};

class CompareNode {
public:
    bool operator()(Node const& n1, Node const& n2) {
        return n1.cost > n2.cost;
    }
};

void BranchAndBound::solve(TSPData& data) {
    int N = data.getCities().size();
    std::vector<std::vector<double> > adjMatrix = data.getAdjacencyMatrix();
    std::priority_queue<Node, std::vector<Node>, CompareNode> pq;
    std::vector<int> initialPath;
    initialPath.push_back(0);

    Node root;
    root.path = initialPath;
    root.vertex = 0;
    root.level = 0;
    root.reducedMatrix = adjMatrix;
    root.reducedMatrixSize = N;
    root.cost = reduceMatrix(root.reducedMatrix, N);

    pq.push(root);

    while (!pq.empty()) {
        Node min = pq.top();
        pq.pop();

        if (min.level == N - 1) {
            min.path.push_back(0);
            solution = min.path;
            return;
        }

        for (int i = 0; i < N; i++) {
            if (min.reducedMatrix[min.vertex][i] != std::numeric_limits<int>::max()) {
                Node child;
                child.level = min.level + 1;
                child.path = min.path;
                child.path.push_back(i);
                child.reducedMatrix = min.reducedMatrix;
                child.vertex = i;
                child.reducedMatrixSize = N;

                for (int j = 0; j < N; j++) {
                    child.reducedMatrix[min.vertex][j] = std::numeric_limits<int>::max();
                    child.reducedMatrix[j][i] = std::numeric_limits<int>::max();
                }
                child.reducedMatrix[i][0] = std::numeric_limits<int>::max();

                child.cost = min.cost + min.reducedMatrix[min.vertex][i] + reduceMatrix(child.reducedMatrix, N);

                pq.push(child);
            }
        }
    }
}

std::vector<int> BranchAndBound::getSolution() const {
    std::vector<int> res = solution;
    res.pop_back();
    return res;
}

int BranchAndBound::reduceMatrix(std::vector<std::vector<double> >& matrix, int N) {
    int cost = 0;

    for (int i = 0; i < N; i++) {
        int rowMin = std::numeric_limits<int>::max();
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] < rowMin)
                rowMin = matrix[i][j];
        }
        if (rowMin != std::numeric_limits<int>::max()) {
            cost += rowMin;
            for (int j = 0; j < N; j++) {
                if (matrix[i][j] != std::numeric_limits<int>::max())
                    matrix[i][j] -= rowMin;
            }
        }
    }

    for (int j = 0; j < N; j++) {
        int colMin = std::numeric_limits<int>::max();
        for (int i = 0; i < N; i++) {
            if (matrix[i][j] < colMin)
                colMin = matrix[i][j];
        }
        if (colMin != std::numeric_limits<int>::max()) {
            cost += colMin;
            for (int i = 0; i < N; i++) {
                if (matrix[i][j] != std::numeric_limits<int>::max())
                    matrix[i][j] -= colMin;
            }
        }
    }

    return cost;
}
