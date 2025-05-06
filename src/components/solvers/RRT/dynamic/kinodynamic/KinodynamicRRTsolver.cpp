//
// Created by arseniy on 20.3.25.
//

#include "KinodynamicRRTsolver.h"

#include <unordered_set>
#include <utils/PhysicsUtils.h>
#include <utils/PositionUtils.h>

std::unique_ptr<IComponent> KinodynamicRRTsolver::createComponent(const ComponentConfig &config, const ReaderContext &context)
{
    const auto& configMap = config.config;

    int maxIterations = static_cast<int>(std::any_cast<double>(configMap.at("maxIterations")));
    int controlInputSamples = static_cast<int>(std::any_cast<double>(configMap.at("controlInputSamples")));
    int outputPeriod = 10000;

    return std::make_unique<KinodynamicRRTsolver>(maxIterations, outputPeriod, controlInputSamples);
}

std::shared_ptr<TreeNode<State>> KinodynamicRRTsolver::findNearestNeighbour(const Keyframe &sample)
{
    std::vector<int> indexes = nnSearch->findKnearestNeighboursIndexes(sample);
    std::unordered_set<std::shared_ptr<TreeNode<State>>> nearestStates;
    auto& nodes = tree->getNodes();
    for (auto index : indexes)
    {
        nearestStates.insert(nodes[index]);
    }
    return chooseBestState(nearestStates, sample);
    //return AKinodynamicRRTsolver<State, Animation, Keyframe, ControlInput>::findNearestNeighbour(sample);
}

std::shared_ptr<TreeNode<State>> KinodynamicRRTsolver::chooseBestState(
    const std::unordered_set<std::shared_ptr<TreeNode<State>>>& nodes, const Keyframe &sample)
{
    using namespace PhysicsUtils;

    double bestScore = -std::numeric_limits<double>::max();
    std::shared_ptr<TreeNode<State>> result;
    for (auto node : nodes)
    {
        std::array<double, 3> direction {
            sample.translation[0] - node->pose.translation[0],
            sample.translation[1] - node->pose.translation[1],
            sample.translation[2] - node->pose.translation[2],
        };
        std::array<double, 3> normalizedDirection = normalize(direction);
        //std::array<double, 3> normalizedVelocity = normalize(node->pose.velocity);
        double score = dot(normalizedDirection, node->pose.velocity);
        if (score > bestScore)
        {
            bestScore = score;
            result = node;
        }
    }
    return result;
}
