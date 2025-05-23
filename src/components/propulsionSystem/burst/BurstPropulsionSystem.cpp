// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "BurstPropulsionSystem.h"

std::unique_ptr<IComponent> BurstPropulsionSystem::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double minProfileDuration = std::any_cast<double>(configMap.at("minProfileDuration"));
    double maxProfileDuration = std::any_cast<double>(configMap.at("maxProfileDuration"));


    return std::make_unique<BurstPropulsionSystem>(minProfileDuration, maxProfileDuration);
}

ControlInputPlan BurstPropulsionSystem::generateControlInputPlan(
    const BurstControlInput &controlInput)
{
    ControlInputPlan controlInputPlan;
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
            controlInput.getThrust(), std::array<double,3> {0.0,0.0,0.0}, secondSegmentDuration, secondSegmentDuration));
    if (thrustBurstDuration < torqueBurstDuration)
        controlInputPlan.addSegment(secondSegmentDuration, std::make_unique<BurstControlInput>(
            0.0, controlInput.getTorque(), secondSegmentDuration, secondSegmentDuration));



    double thirdSegmentDuration = profileDurationDistribution(gen) - secondSegmentDuration - firstSegmentDuration;
    if (thirdSegmentDuration < 0)
    {
        spdlog::error("Propulsion system - inconsistent profile duration.");
        throw std::runtime_error("Propulsion system - inconsistent profile duration.");
    }

    controlInputPlan.addSegment(thirdSegmentDuration, std::make_unique<BurstControlInput>(
        0.0, std::array<double,3> {0.0,0.0,0.0}, thirdSegmentDuration, thirdSegmentDuration));
    return controlInputPlan;
}
