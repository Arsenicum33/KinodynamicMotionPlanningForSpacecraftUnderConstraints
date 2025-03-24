//
// Created by arseniy on 20.3.25.
//

#ifndef CONTROLINPUTSAMPLER_H
#define CONTROLINPUTSAMPLER_H
#include <random>

#include "IControlInputSampler.h"


class ControlInputSampler : public IControlInputSampler<ControlInput>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    ControlInputSampler(double maxLinearAccelerationModule,
        std::array<double, 3> maxAngularAccelerationModules)
        : maxLinearAccelerationModule(maxLinearAccelerationModule),
          maxAngularAccelerationModules(maxAngularAccelerationModules),
        linearAccelerationDist(0, maxLinearAccelerationModule),
        angularAccelerationRollDist(-maxAngularAccelerationModules[0], maxAngularAccelerationModules[0]),
        angularAccelerationPitchDist(-maxAngularAccelerationModules[1], maxAngularAccelerationModules[1]),
        angularAccelerationYawDist(-maxAngularAccelerationModules[2], maxAngularAccelerationModules[2])
    {}

    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::KinodynamicEnv}; };

    ControlInput sample() override;

protected:
    double maxLinearAccelerationModule;
    std::array<double, 3> maxAngularAccelerationModules;
    std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<double> linearAccelerationDist;
    std::uniform_real_distribution<double> angularAccelerationRollDist;
    std::uniform_real_distribution<double> angularAccelerationPitchDist;
    std::uniform_real_distribution<double> angularAccelerationYawDist;
};



#endif //CONTROLINPUTSAMPLER_H
