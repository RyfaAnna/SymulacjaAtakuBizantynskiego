#include "Graphs.h"


std::vector<std::vector<int> > Graphs::generate_complete_graph(int N) {
    std::vector<std::vector<int> > adjacency_list(N);
    for (int i = 0; i < N; ++i) {
        adjacency_list[i].reserve(N - 1);
        for (int j = 0; j < N; ++j) {
            if (i != j) {
                adjacency_list[i].push_back(j);
            }
        }
    }
    return adjacency_list;
}

std::vector<std::vector<int> > Graphs::generate_erdos_renyi_graph(int N) {
    std::vector<std::vector<int> > adjacency_list(N);
    for (int i = 0; i < N; ++i) {
        adjacency_list[i].reserve(N - 1);
        for (int j = i + 1; j < N; ++j) {
            if (RandomGenerator::random_real() > 0.2) {
                adjacency_list[i].push_back(j);
                adjacency_list[j].push_back(i);
            }
        }
    }
    if (not isConnected(adjacency_list)) {
        adjacency_list.clear();
        generate_erdos_renyi_graph(N);
    }
    return adjacency_list;
}

void Graphs::DFS(int v, std::vector<bool> &visited, const std::vector<std::vector<int> > &adjList) {
    visited[v] = true;
    for (int neighbor: adjList[v]) {
        if (!visited[neighbor]) {
            DFS(neighbor, visited, adjList);
        }
    }
}

bool Graphs::isConnected(const std::vector<std::vector<int> > &adjacency_list) {
    int numVertices = adjacency_list.size();
    std::vector<bool> visited(numVertices, false);

    DFS(0, visited, adjacency_list);

    for (int i = 0; i < numVertices; ++i) {
        if (!visited[i]) {
            return false;
        }
    }
    return true;
}

std::vector<std::vector<int> > Graphs::generateGraph(int N, GraphType graphType) {
    switch (graphType) {
        case GraphType::Complete:
            return generate_complete_graph(N);
        case GraphType::Erdos_Renyi:
            return generate_erdos_renyi_graph(N);
    }
    return std::vector<std::vector<int> >();
}
