//
// Created by arseniy on 23.10.24.
//

#include "SolverFactory.h"

#include "../treeSolvers/RRT*/RrtStarSolver.h"
#include "../treeSolvers/RRT/RRTsolver.h"
#include <iostream>

#include "../../collisionHandlers/ICollisionHandler.h"
#include "../../collisionHandlers/RapidCollisionHandler.h"
#include "../../distanceMeasurement/WeightedTranslationRotationMetric.h"
#include "../../meshParsers/MeshParser.h"
#include "../../meshParsers/RapidObjMeshParser.h"
#include "../../nearestNeighbour/BruteForceNNsearch.h"
#include "../../nearestNeighbour/MPNNsearch.h"
#include "../../pathGenerator/UniformPathGenerator.h"
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
        std::unique_ptr<AbstractNearestNeighbourSearch> nnSearch = std::make_unique<MPNNsearch>(distanceMetric, 6, 10);
        std::unique_ptr<IPoseSampler> sampler = std::make_unique<BiasedRandomSampler>(
            envSettings.boundaries, config.goalBias, envSettings.endPose);
        RapidObjMeshParser parser;
        std::unique_ptr<ICollisionHandler> collisionHandler = std::make_unique<RapidCollisionHandler>(
            envSettings.agentFilepath, envSettings.obstaclesFilepath,parser);

        std::unique_ptr<IPathGenerator> pathGenerator = std::make_unique<UniformPathGenerator>(config.interpolationDistanceThreshold,
            config.interpolationRotationDistanceThreshold, 400);
        auto solver = std::make_unique<RRTsolver>(config, envSettings, distanceMetric, std::move(nnSearch), std::move(sampler), std::move(collisionHandler),
            std::move(pathGenerator));
        return solver;
    }

    if (algorithm == "RRT*")
    {
        auto config = RrtStarSolverConfig::fromJson(jsonConfig);
        auto distanceMetric = std::make_shared<WeightedTranslationRotationMetric>(config.rotationScalingFactor);
        std::unique_ptr<AbstractNearestNeighbourSearch> nnSearch = std::make_unique<MPNNsearch>(distanceMetric, 6, 10);
        std::unique_ptr<IPoseSampler> sampler = std::make_unique<BiasedRandomSampler>(
            envSettings.boundaries, config.goalBias, envSettings.endPose);
        RapidObjMeshParser parser;
        std::unique_ptr<ICollisionHandler> collisionHandler = std::make_unique<RapidCollisionHandler>(
            envSettings.agentFilepath, envSettings.obstaclesFilepath,parser);
        std::unique_ptr<IPathGenerator> pathGenerator = std::make_unique<UniformPathGenerator>(config.interpolationDistanceThreshold,
    config.interpolationRotationDistanceThreshold, 400);
        auto solver = std::make_unique<RrtStarSolver>(config, envSettings, distanceMetric, std::move(nnSearch), std::move(sampler),
            std::move(collisionHandler), std::move(pathGenerator));
        return solver;
    }

    throw std::runtime_error("Unknown algorithm.");
}
