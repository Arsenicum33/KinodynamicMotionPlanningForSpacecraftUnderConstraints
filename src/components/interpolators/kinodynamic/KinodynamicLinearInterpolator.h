// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef KINODYNAMICLINEARINTERPOLATOR_H
#define KINODYNAMICLINEARINTERPOLATOR_H
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "components/interpolators/AInterpolator.h"

class KinodynamicLinearInterpolator : public AInterpolator<State>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    KinodynamicLinearInterpolator(double interpolationTimestep)
        : interpolationTimestep(interpolationTimestep) {}


    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::KinodynamicEnv}; }

protected:
    int calculateInterpolationSteps(const State &from, const State &to) override;

    State interpolateBetweenPositions(const State &start, const State &end, double factor) override;

private:
    double interpolationTimestep;

};



#endif //KINODYNAMICLINEARINTERPOLATOR_H
