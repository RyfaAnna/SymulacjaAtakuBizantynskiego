#ifndef SOCIALIMPACTMODEL_H
#define SOCIALIMPACTMODEL_H

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>

#include "Graphs.h"


enum class BizStrategyKind {
    Random,
    Opposite,
    StickToStart,
    Mix
};

class SocialImpactModel {
public:
    SocialImpactModel(int N, int num_byzantine, int max_steps, double temperature, double opinionsExpiration,
                      BizStrategyKind bizStrategyKind, Graphs::GraphType graphType);

    void run_simulation();

    bool isSuccess() const;

    double calculate_influence(int i);

    int bizantianOpinion(int i, int my_opinion, BizStrategyKind strategy);


    int random_opinion() {
        return (RandomGenerator::random_real() < 0.5) ? -1 : 1;
    }

    double custom_function(double influence, double temperature) {
        return 1.0 / (1.0 + std::exp(-(influence) / temperature));
    }

private:
    int N, num_byzantine, max_steps;
    double temperature;
    double opinionsExpiration;
    std::vector<int> opinions;
    std::vector<double> totInfluence;
    std::vector<int> startOpinions;
    std::vector<int> positiveOpinions;
    std::vector<int> negativeOpinions;
    std::vector<double> positiveOpinionsCalc;
    std::vector<double> negativeOpinionsCalc;
    std::vector<int> new_opinions;
    std::vector<std::vector<int> > adjacency_list;
    BizStrategyKind kindOfBizantianStrategy;
    BizStrategyKind randomStrategyForMixOption;
    Graphs::GraphType graphType;
};
#endif //SOCIALIMPACTMODEL_H
