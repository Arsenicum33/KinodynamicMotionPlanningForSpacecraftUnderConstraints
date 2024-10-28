//
// Created by arseniy on 23.10.24.
//

#include "SolverFactory.h"

#include "../treeSolvers/RRT*/RrtStarSolver.h"
#include "../treeSolvers/RRT/RRTsolver.h"
#include <iostream>

#include "../../distanceMeasurement /WeightedTranslationRotationMetric.h"
#include "../../nearestNeighbour/BruteForceNNsearch.h"
#include "../../poses/sampling/BiasedRandomSampler.h"


std::unique_ptr<AbstractSolver> SolverFactory::createSolverFromConfig(const std::string &filepath, const EnvSettings &envSettings)
{
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open config file: " + filepath);
    }

    Json::CharReaderBuilder reader;
    Json::Value jsonConfig;
    std::string errors;

    if (!parseFromStream(reader, file, &jsonConfig, &errors))
    {
        throw std::runtime_error("Failed to parse JSON: " + errors);
    }

    std::string algorithm = jsonConfig["algorithm"].asString();

    if (algorithm == "RRT")
    {
        auto config = RRTsolverConfig::fromJson(jsonConfig);
        auto distanceMetric = std::make_shared<WeightedTranslationRotationMetric>(config.rotationScalingFactor);
        std::unique_ptr<AbstractNearestNeighbourSearch> nnSearch = std::make_unique<BruteForceNNsearch>(distanceMetric);
        std::unique_ptr<IPoseSampler> sampler = std::make_unique<BiasedRandomSampler>(
            envSettings.boundaries, config.goalBias, envSettings.endPose);

        auto solver = std::make_unique<RRTsolver>(config, envSettings, distanceMetric, std::move(nnSearch), std::move(sampler));
        return solver;
    }

    if (algorithm == "RRT*")
    {
        auto config = RrtStarSolverConfig::fromJson(jsonConfig);
        auto solver = RrtStarSolver(config, envSettings);
        return std::make_unique<RrtStarSolver>(solver);
    }

    throw std::runtime_error("Unknown algorithm.");
}
