//
// Created by arseniy on 3.1.25.
//

#ifndef CAPABILITY_H
#define CAPABILITY_H
#include <set>
#include <string>

enum class Capability
{
    StaticEnv,
    DynamicEnv,
    MovingTarget
};

using CapabilitySet = std::set<Capability>;

inline std::string capabilityToString(Capability cap)
{
    switch (cap)
    {
        case Capability::StaticEnv: return "StaticEnv";
        case Capability::DynamicEnv: return "DynamicEnv";
        case Capability::MovingTarget: return "MovingTarget";
    }
    return "";
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
