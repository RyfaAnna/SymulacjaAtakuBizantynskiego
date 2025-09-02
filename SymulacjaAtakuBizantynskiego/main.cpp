#include "SocialImpactModel.h"

int main() {
    const int num_simulations = 1000;

    constexpr int N = 32;
    int global_simulation_id = 0;
    constexpr double temperatureValues[] = {0.1, 0.15, 0.2, 0.25, 0.3, 0.4};
    constexpr int numByzantineValues[] = {4, 6, 8, 10, 12, 14, 16};
    constexpr int maxSteps[] = {10000};
    constexpr double opinionsExpirations[] = {0.6};
    BizStrategyKind kind = BizStrategyKind::Mix;
    Graphs::GraphType graphType = Graphs::GraphType::Complete;

    for (const auto opinionsExpiration: opinionsExpirations) {
        for (const auto num_byzantine: numByzantineValues) {
            for (const auto maxStep: maxSteps) {
                for (const auto temperature: temperatureValues) {
                    int successCount = 0;
                    for (int simulation_id = 1; simulation_id <= num_simulations;
                         ++simulation_id, ++global_simulation_id) {
                        SocialImpactModel model(N, num_byzantine, maxStep, temperature, opinionsExpiration, kind,
                                                graphType);
                        model.run_simulation();
                        if (model.isSuccess())
                            ++successCount;
                    }
                    std::cout << num_byzantine << ", " << maxStep << ", " << temperature << ", " << opinionsExpiration
                            << " result: " << successCount << std::endl;
                }
            }
        }
    }
    std::cout << "Symulacje zakonczone " << "\n";
    return 0;
}
