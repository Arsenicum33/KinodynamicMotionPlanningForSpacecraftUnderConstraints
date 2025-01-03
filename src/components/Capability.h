//
// Created by arseniy on 3.1.25.
//

#ifndef CAPABILITY_H
#define CAPABILITY_H
#include <set>

enum class Capability
{
    StaticEnv,
    DynamicEnv
};

using CapabilitySet = std::set<Capability>;

#endif //CAPABILITY_H
