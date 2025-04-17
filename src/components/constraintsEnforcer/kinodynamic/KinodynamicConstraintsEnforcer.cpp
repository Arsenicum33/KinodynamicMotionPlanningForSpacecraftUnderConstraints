//
// Created by arseniy on 26.3.25.
//

#include "KinodynamicConstraintsEnforcer.h"

#include <utils/PhysicsUtils.h>

std::unique_ptr<IComponent> KinodynamicConstraintsEnforcer::createComponent(const ComponentConfig &config,
                                                                            const ReaderContext &context)
{
    const auto& configMap = config.config;

    double maxTime = std::any_cast<double>(configMap.at("maxTime"));
    double maxAngularVelocity = std::any_cast<double>(context.sharedVariables.at("maxAngularVelocity"));
    double maxVelocity = std::any_cast<double>(configMap.at("maxVelocity"));
    return std::make_unique<KinodynamicConstraintsEnforcer>(maxAngularVelocity, maxTime, maxVelocity);
}

bool KinodynamicConstraintsEnforcer::satisfiesConstraints(const State &position) const
{
    using namespace PhysicsUtils;
    for (int i=0;i<3;i++)
    {
        if (std::abs(position.angularVelocity[i]) > maxAngularVelocity)
            return false;
    }
    if (position.time > maxTime)
        return false;
    if (norm(position.velocity) > maxVelocity)
        return false;
    return true;

}
