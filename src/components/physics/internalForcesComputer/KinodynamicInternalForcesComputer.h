//
// Created by arseniy on 8.5.25.
//

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
