//
// Created by arseniy on 26.3.25.
//

#ifndef STABILIZINGCONTROLINPUTSAMPLER_H
#define STABILIZINGCONTROLINPUTSAMPLER_H
#include <random>
#include <components/sampling/controlInputSampling/IControlInputSampler.h>
#include <dto/poses/dynamic/kinodynamic/state/State.h>


class StabilizingControlInputSampler : public IControlInputSampler<ControlInput, State>
{
public:
    StabilizingControlInputSampler(double maxLinearAccelerationModule,
        std::array<double, 3> maxAngularAccelerationModules,
        double stabilizingFactor,
        double maxAngularVelocity,
        double sigma)
        : maxLinearAccelerationModule(maxLinearAccelerationModule),
          maxAngularAccelerationModules(maxAngularAccelerationModules),
          linearAccelerationDist(0, maxLinearAccelerationModule),
          stabilizingFactor(stabilizingFactor),
          maxAngularVelocity(maxAngularVelocity),
          sigma(sigma) {}

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::KinodynamicEnv}; }

    ControlInput sample(const State &currentPosition) override;

protected:
    double maxLinearAccelerationModule;
    std::array<double, 3> maxAngularAccelerationModules;
    std::uniform_real_distribution<double> linearAccelerationDist;

private:
    double stabilizingFactor;
    double maxAngularVelocity;
    double sigma;
};



#endif //STABILIZINGCONTROLINPUTSAMPLER_H
