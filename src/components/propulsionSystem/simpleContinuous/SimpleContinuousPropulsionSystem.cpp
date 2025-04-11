//
// Created by arseniy on 7.4.25.
//

#include "SimpleContinuousPropulsionSystem.h"


std::unique_ptr<IComponent> SimpleContinuousPropulsionSystem::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double profileDuration = std::any_cast<double>(configMap.at("profileDuration"));

    return std::make_unique<SimpleContinuousPropulsionSystem>(inputDuration);
}

ControlInputPlan<ControlInput> SimpleContinuousPropulsionSystem::generateControlInputPlan(
    const ControlInput &controlInput)
{
    ControlInputPlan<ControlInput> controlInputPlan;
    controlInputPlan.addSegment(this->profileDuration, std::make_unique<ControlInput>(controlInput));
    return controlInputPlan;
}
