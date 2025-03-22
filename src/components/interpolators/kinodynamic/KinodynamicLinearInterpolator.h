//
// Created by arseniy on 22.3.25.
//

#ifndef KINODYNAMICLINEARINTERPOLATOR_H
#define KINODYNAMICLINEARINTERPOLATOR_H
#include "IKinodynamicInterpolator.h"
#include "components/interpolators/dynamic/IDynamicInterpolator.h"


class KinodynamicLinearInterpolator : public IKinodynamicInterpolator
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    KinodynamicLinearInterpolator(double interpolationTimestep, double maxInterpolationTimeDifference)
        : interpolationTimestep(interpolationTimestep),
          maxInterpolationTimeDifference(maxInterpolationTimeDifference) {}


    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::MovingTarget}; }

    std::vector<State> interpolate(const State &start, const State &end) override;

    State getIntermediatePosition(const State &from, const State &to, double stepSize) override;


private:
    double interpolationTimestep;
    double maxInterpolationTimeDifference;

};



#endif //KINODYNAMICLINEARINTERPOLATOR_H
