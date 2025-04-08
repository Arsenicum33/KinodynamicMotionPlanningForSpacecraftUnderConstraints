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
    explicit BurstPropulsionSystem(double maxTotalProfileDuration, double burstMaxDuration)
        : maxTotalProfileDuration(maxTotalProfileDuration),
    burstMaxDuration(burstMaxDuration),
        burstDurationDist(burstMaxDuration, maxTotalProfileDuration) {}

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::KinodynamicEnv, Capability::AstrodynamicEnv}; }

    ComponentType getType() const override { return ComponentType::PropulsionSystem; }

private:
    std::uniform_real_distribution<double> burstDurationDist;
    AccelerationProfile<BurstControlInput> generateAccelerationProfile(const BurstControlInput &controlInput) override;
    double maxTotalProfileDuration;
    double burstMaxDuration;

    std::mt19937 gen{std::random_device{}()};
};



#endif //BURSTPROPULSIONSYSTEM_H
