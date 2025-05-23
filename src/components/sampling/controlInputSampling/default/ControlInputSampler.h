// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef CONTROLINPUTSAMPLER_H
#define CONTROLINPUTSAMPLER_H
#include <random>
#include <dto/poses/dynamic/kinodynamic/state/State.h>
#include "components/sampling/controlInputSampling/IControlInputSampler.h"

class ControlInputSampler : public IControlInputSampler<ControlInput, State>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    ControlInputSampler(double thrust,
        std::array<double, 3> torque)
        : thrust(thrust),
          torque(torque),
        thrustDist(0, thrust),
        torqueRollDist(-torque[1], torque[1]),
        torquePitchDist(-torque[0], torque[0]),
        torqueYawDist(-torque[2], torque[2])
    {}

    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::KinodynamicEnv}; };

    ControlInput sample(const State& currentPosition) override;

protected:
    double thrust;
    std::array<double, 3> torque;
    std::uniform_real_distribution<double> thrustDist;
    std::uniform_real_distribution<double> torqueRollDist; // Y axis (forward axis)
    std::uniform_real_distribution<double> torquePitchDist; // X axis
    std::uniform_real_distribution<double> torqueYawDist; // Z axis
};



#endif //CONTROLINPUTSAMPLER_H
