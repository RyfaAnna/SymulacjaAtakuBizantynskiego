#ifndef GRAPHS_H
#define GRAPHS_H

#include <vector>
#include <random>


class RandomGenerator {
public:
    static double random_real() {
        return std::uniform_real_distribution<>(0.0, 1.0)(engine);
    }

private:
    inline static std::mt19937 engine{std::random_device{}()};
};

class Graphs {
public:
    enum class GraphType {
        Complete,
        Erdos_Renyi
    };

    static std::vector<std::vector<int> > generate_complete_graph(int N);

    static std::vector<std::vector<int> > generate_erdos_renyi_graph(int N);

    static void DFS(int v, std::vector<bool> &visited, const std::vector<std::vector<int> > &adjList);

    static bool isConnected(const std::vector<std::vector<int> > &adjacency_list);

    static std::vector<std::vector<int> > generateGraph(int N, GraphType graphType);
};


#endif //GRAPHS_H
