#include "SocialImpactModel.h"


SocialImpactModel::SocialImpactModel(int N, int num_byzantine, int max_steps, double temperature,
                                     double opinionsExpiration, BizStrategyKind bizStrategyKind,
                                     Graphs::GraphType graphType)
    : N(N), num_byzantine(num_byzantine), max_steps(max_steps),
      temperature(temperature), opinionsExpiration(opinionsExpiration), opinions(N), startOpinions(N),
      positiveOpinions(N), negativeOpinions(N), positiveOpinionsCalc(N), negativeOpinionsCalc(N), new_opinions(N),
      kindOfBizantianStrategy(bizStrategyKind), graphType(graphType) {
    for (int i = 0; i < N - num_byzantine; ++i) {
        opinions[i] = random_opinion();
        startOpinions[i] = opinions[i];
    }
    for (int i = N - num_byzantine; i < N; ++i) {
        opinions[i] = 0;
    }
    randomStrategyForMixOption = RandomGenerator::random_real() < 0.5
                                     ? BizStrategyKind::StickToStart
                                     : BizStrategyKind::Opposite;

    adjacency_list = Graphs::generateGraph(N, graphType);
}

void SocialImpactModel::run_simulation() {
    for (int step = 0; step < max_steps; ++step) {
        for (int i = 0; i < N - num_byzantine; ++i) {
            double influence = calculate_influence(i);
            double probability_of_change = custom_function(influence, temperature);

            if (RandomGenerator::random_real() < probability_of_change) {
                new_opinions[i] = -opinions[i];
            } else {
                new_opinions[i] = opinions[i];
            }
        }

        opinions = new_opinions;
        for (int i = 0; i < N - num_byzantine; ++i) {
            if (opinions[i] == 1) ++positiveOpinions[i];
            else ++negativeOpinions[i];
        }
    }
}

bool SocialImpactModel::isSuccess() const {
    std::vector<int> final_majority_opinions;

    for (int i = 0; i < N - num_byzantine; ++i) {
        if (positiveOpinions[i] > negativeOpinions[i])
            final_majority_opinions.push_back(1);
        else if (negativeOpinions[i] > positiveOpinions[i])
            final_majority_opinions.push_back(-1);
        else
            return false;
    }

    int reference = final_majority_opinions[0];
    for (size_t i = 1; i < final_majority_opinions.size(); ++i) {
        if (final_majority_opinions[i] != reference)
            return false;
    }
    return true;
}

int SocialImpactModel::bizantianOpinion(int i, int my_opinion, BizStrategyKind strategy) {
    switch (strategy) {
        case BizStrategyKind::Random:
            return random_opinion();
        case BizStrategyKind::Opposite:
            return (my_opinion == 1 ? -1 : 1);
        case BizStrategyKind::StickToStart:
            return startOpinions[i];
        case BizStrategyKind::Mix:
            return bizantianOpinion(i, my_opinion, randomStrategyForMixOption);
    }
}

double SocialImpactModel::calculate_influence(int i) {
    int influence = 0;
    int posOp = 0;
    int negOp = 0;
    auto my_opinion = opinions[i];

    auto &adjList = adjacency_list[i];
    for (int neighbor: adjList) {
        int opinion_j = neighbor >= N - num_byzantine
                            ? bizantianOpinion(i, my_opinion, kindOfBizantianStrategy)
                            : opinions[neighbor];
        if (opinion_j == -1) ++negOp;
        else ++posOp;
    }
    positiveOpinionsCalc[i] = positiveOpinionsCalc[i] * opinionsExpiration + posOp;
    negativeOpinionsCalc[i] = negativeOpinionsCalc[i] * opinionsExpiration + negOp;

    influence = my_opinion == -1
                    ? positiveOpinionsCalc[i] - negativeOpinionsCalc[i]
                    : negativeOpinionsCalc[i] - positiveOpinionsCalc[i];

    return static_cast<double>(influence) / adjacency_list[i].size();
}
