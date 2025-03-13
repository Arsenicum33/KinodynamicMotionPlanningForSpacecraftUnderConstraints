//
// Created by arseniy on 3.1.25.
//

#ifndef CAPABILITY_H
#define CAPABILITY_H
#include <set>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include "spdlog/spdlog.h"

enum class Capability
{
    StaticEnv,
    DynamicEnv,
    MovingTarget
};

using CapabilitySet = std::set<Capability>;

inline const std::unordered_map<Capability, std::string> capabilityToStringMap =
{
    { Capability::StaticEnv, "StaticEnv"},
    { Capability::DynamicEnv, "DynamicEnv"},
    { Capability::MovingTarget, "MovingTarget"}
};

inline const std::unordered_map<std::string, Capability> stringToCapabilityMap = []
{
    std::unordered_map<std::string, Capability> reverseMap;
    for (const auto &[key, value] : capabilityToStringMap)
    {
        reverseMap[value] = key;
    }
    return reverseMap;
}();

inline std::string capabilityToString(Capability capability)
{
    auto it = capabilityToStringMap.find(capability);
    if (it != capabilityToStringMap.end())
    {
        return it->second;
    }
    spdlog::error("Invalid Capability type");
    throw std::invalid_argument("Invalid Capability type");
}

inline Capability stringToCapability(const std::string &str)
{
    auto it = stringToCapabilityMap.find(str);
    if (it != stringToCapabilityMap.end())
    {
        return it->second;
    }
    spdlog::error("Invalid Capability type string: {}", str);
    throw std::invalid_argument("Invalid Capability string: " + str);
}

inline std::string capabilitySetToString(CapabilitySet set)
{
    std::string result;
    for (auto cap : set)
    {
        result += capabilityToString(cap);
        result += " ";
    }
    return result;
}


#endif //CAPABILITY_H
