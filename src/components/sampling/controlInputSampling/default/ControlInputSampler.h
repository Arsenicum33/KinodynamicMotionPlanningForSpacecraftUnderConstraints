//
// Created by arseniy on 20.3.25.
//

#ifndef CONTROLINPUTSAMPLER_H
#define CONTROLINPUTSAMPLER_H
#include <random>
#include <dto/poses/dynamic/kinodynamic/state/State.h>
#include "components/sampling/controlInputSampling/IControlInputSampler.h"

class ControlInputSampler : public IControlInputSampler<ControlInput, State>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    ControlInputSampler(double maxLinearAccelerationModule,
        std::array<double, 3> maxAngularAccelerationModules)
        : maxLinearAccelerationModule(maxLinearAccelerationModule),
          maxAngularAccelerationModules(maxAngularAccelerationModules),
        linearAccelerationDist(0, maxLinearAccelerationModule),
        angularAccelerationRollDist(-maxAngularAccelerationModules[1], maxAngularAccelerationModules[1]),
        angularAccelerationPitchDist(-maxAngularAccelerationModules[0], maxAngularAccelerationModules[0]),
        angularAccelerationYawDist(-maxAngularAccelerationModules[2], maxAngularAccelerationModules[2])
    {}

    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::KinodynamicEnv}; };

    ControlInput sample(const State& currentPosition) override;

protected:
    double maxLinearAccelerationModule;
    std::array<double, 3> maxAngularAccelerationModules;
    std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<double> linearAccelerationDist;
    std::uniform_real_distribution<double> angularAccelerationRollDist; // Y axis (forward axis)
    std::uniform_real_distribution<double> angularAccelerationPitchDist; // X axis
    std::uniform_real_distribution<double> angularAccelerationYawDist; // Z axis
};



#endif //CONTROLINPUTSAMPLER_H
