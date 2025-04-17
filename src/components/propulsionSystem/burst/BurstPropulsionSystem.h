//
// Created by arseniy on 7.4.25.
//

#ifndef BURSTPROPULSIONSYSTEM_H
#define BURSTPROPULSIONSYSTEM_H
#include <random>

#include "components/propulsionSystem/IPropulsionSystem.h"
#include "dto/poses/dynamic/kinodynamic/burstControlInput/BurstControlInput.h"


class BurstPropulsionSystem : public IPropulsionSystem<BurstControlInput>
{
public:
    explicit BurstPropulsionSystem(double minProfileDuration, double maxProfileDuration )
        : maxProfileDuration(maxProfileDuration), minProfileDuration(minProfileDuration),
            profileDurationDistribution(minProfileDuration, maxProfileDuration){}

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::KinodynamicEnv, Capability::AstrodynamicEnv}; }

    ComponentType getType() const override { return ComponentType::PropulsionSystem; }

    ControlInputPlan<BurstControlInput> generateControlInputPlan(const BurstControlInput &controlInput) override;
private:
    double maxProfileDuration;
    double minProfileDuration;
    std::uniform_real_distribution<double> profileDurationDistribution;
    std::mt19937 gen{std::random_device{}()};
};



#endif //BURSTPROPULSIONSYSTEM_H
