// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef STABILIZINGCONTROLINPUTSAMPLER_H
#define STABILIZINGCONTROLINPUTSAMPLER_H
#include <random>
#include <components/sampling/controlInputSampling/IControlInputSampler.h>
#include <dto/poses/dynamic/kinodynamic/state/State.h>


class StabilizingControlInputSampler : public IControlInputSampler<ControlInput, State>
{
public:
    StabilizingControlInputSampler(double thrust,
        std::array<double, 3> torque,
        double stabilizingFactor,
        double maxAngularVelocity,
        double sigma)
        : thrust(thrust),
          torque(torque),
          thrustDist(0, thrust),
          stabilizingFactor(stabilizingFactor),
          maxAngularVelocity(maxAngularVelocity),
          sigma(sigma) {}

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::KinodynamicEnv}; }

    ControlInput sample(const State &currentPosition) override;

protected:
    double thrust;
    std::array<double, 3> torque;
    std::uniform_real_distribution<double> thrustDist;

private:
    double stabilizingFactor;
    double maxAngularVelocity;
    double sigma;
};



#endif //STABILIZINGCONTROLINPUTSAMPLER_H
