//
// Created by arseniy on 23.10.24.
//

#include "SolverFactory.h"

#include "../treeSolvers/RRT*/RrtStarSolver.h"
#include "../treeSolvers/RRT/RRTsolver.h"

std::unique_ptr<AbstractSolver> SolverFactory::createSolverFromConfig(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open config file.");
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
        auto solver = RRTsolver(config);
        return std::make_unique<RRTsolver>(solver);
    }

    if (algorithm == "RRT*")
    {
        auto config = RrtStarSolverConfig::fromJson(jsonConfig);
        auto solver = RrtStarSolver(config);
        return std::make_unique<RrtStarSolver>(solver);
    }

    throw std::runtime_error("Unknown algorithm.");
}
