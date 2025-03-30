//
// Created by arseniy on 26.3.25.
//

#include "ConstraintsEnforcer.h"

std::unique_ptr<IComponent> ConstraintsEnforcer::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double maxTime = std::any_cast<double>(configMap.at("maxTime"));
    double maxAngularVelocity = std::any_cast<double>(context.sharedVariables.at("maxAngularVelocity"));
    return std::make_unique<ConstraintsEnforcer>(maxAngularVelocity, maxTime);
}

bool ConstraintsEnforcer::satisfiesConstraints(const State &position) const
{
    for (int i=0;i<3;i++)
    {
        if (std::abs(position.angularVelocity[i]) > maxAngularVelocity)
            return false;
    }
    if (position.time > maxTime)
        return false;

    return true;

}
