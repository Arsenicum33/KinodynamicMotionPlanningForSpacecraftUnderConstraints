//
// Created by arseniy on 13.3.25.
//

#ifndef COMPONENTTYPE_H
#define COMPONENTTYPE_H
#include <spdlog/spdlog.h>


enum class ComponentType
{
    CollisionHandler,
    DistanceMetric,
    Exporter,
    NearestNeighbourSearch,
    PathGenerator,
    Sampler,
    Solver,
    TerminationCondition
};

inline const std::unordered_map<ComponentType, std::string> componentTypeToStringMap = {
    {ComponentType::CollisionHandler, "CollisionHandler"},
    {ComponentType::DistanceMetric, "DistanceMetric"},
    {ComponentType::Exporter, "Exporter"},
    {ComponentType::NearestNeighbourSearch, "NearestNeighbourSearch"},
    {ComponentType::PathGenerator, "PathGenerator"},
    {ComponentType::Sampler, "Sampler"},
    {ComponentType::Solver, "Solver"},
    {ComponentType::TerminationCondition, "TerminationCondition"}
};

inline const std::unordered_map<std::string, ComponentType> stringToComponentTypeMap = [] {
    std::unordered_map<std::string, ComponentType> reverseMap;
    for (const auto &[key, value] : componentTypeToStringMap)
    {
        reverseMap[value] = key;
    }
    return reverseMap;
}();

inline std::string componentTypeToString(ComponentType type)
{
    auto it = componentTypeToStringMap.find(type);
    if (it != componentTypeToStringMap.end())
    {
        return it->second;
    }
    spdlog::error("Invalid component type");
    throw std::invalid_argument("Invalid ComponentType");
}

inline ComponentType stringToComponentType(const std::string &str)
{
    auto it = stringToComponentTypeMap.find(str);
    if (it != stringToComponentTypeMap.end())
    {
        return it->second;
    }
    spdlog::error("Invalid component type string {}", str);
    throw std::invalid_argument("Invalid ComponentType string: " + str);
}

#endif //COMPONENTTYPE_H
