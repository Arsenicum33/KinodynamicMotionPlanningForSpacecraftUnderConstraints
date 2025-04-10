//
// Created by arseniy on 7.4.25.
//

#include "BurstPropulsionSystem.h"

std::unique_ptr<IComponent> BurstPropulsionSystem::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double profileDuration = std::any_cast<double>(configMap.at("profileDuration"));


    return std::make_unique<BurstPropulsionSystem>(profileDuration);
}

ControlInputPlan<BurstControlInput> BurstPropulsionSystem::generateAccelerationProfile(
    const BurstControlInput &controlInput)
{
    ControlInputPlan<BurstControlInput> controlInputPlan;
    double thrustBurstDuration = controlInput.getThrustBurstDuration();
    double torqueBurstDuration = controlInput.getTorqueBurstDuration();

    double firstSegmentDuration = std::min(thrustBurstDuration, torqueBurstDuration);
    controlInputPlan.addSegment(firstSegmentDuration,
        std::make_unique<BurstControlInput>(controlInput.getThrust(), controlInput.getTorque(),
            firstSegmentDuration, firstSegmentDuration
    ));

    double secondSegmentDuration = std::max(thrustBurstDuration, torqueBurstDuration) - firstSegmentDuration;
    if (thrustBurstDuration > torqueBurstDuration)
        controlInputPlan.addSegment(secondSegmentDuration, std::make_unique<BurstControlInput>(
            thrustBurstDuration, std::array<double,3> {0.0,0.0,0.0}, secondSegmentDuration, secondSegmentDuration));
    if (thrustBurstDuration < torqueBurstDuration)
        controlInputPlan.addSegment(secondSegmentDuration, std::make_unique<BurstControlInput>(
            0.0, controlInput.getTorque(), secondSegmentDuration, secondSegmentDuration));

    double thirdSegmentDuration = profileDuration - secondSegmentDuration - firstSegmentDuration;
    if (thirdSegmentDuration < 0)
    {
        spdlog::error("Propulsion system - inconsistent profile duration.");
        throw std::runtime_error("Propulsion system - inconsistent profile duration.");
    }

    controlInputPlan.addSegment(thirdSegmentDuration, std::make_unique<BurstControlInput>(
        0.0, std::array<double,3> {0.0,0.0,0.0}, thirdSegmentDuration, thirdSegmentDuration));
    return controlInputPlan;
}
