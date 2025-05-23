// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef KINODYNAMICINTERNALFORCESCOMPUTER_H
#define KINODYNAMICINTERNALFORCESCOMPUTER_H
#include "InternalForcesComputer.h"

class KinodynamicInternalForcesComputer : public InternalForcesComputer<State>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::KinodynamicEnv};};
};

inline std::unique_ptr<IComponent> KinodynamicInternalForcesComputer::createComponent(
    const ComponentConfig &config, const ReaderContext &context)
{
    return std::make_unique<KinodynamicInternalForcesComputer>();
}

#endif //KINODYNAMICINTERNALFORCESCOMPUTER_H
