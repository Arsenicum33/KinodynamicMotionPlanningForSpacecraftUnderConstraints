//
// Created by arseniy on 9.5.25.
//

#ifndef KINODYNAMICBIASEDSAMPLER_H
#define KINODYNAMICBIASEDSAMPLER_H
#include <components/sampling/positionSampling/ABiasedRandomSampler.h>
#include <dto/poses/dynamic/kinodynamic/state/State.h>


class KinodynamicBiasedSampler : public ABiasedRandomSampler<State, Animation>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    KinodynamicBiasedSampler(const ConfigurationSpaceBoundaries &boundaries, double goalBias)
        : ABiasedRandomSampler<State, Animation>(boundaries, goalBias) {}
    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::KinodynamicEnv}; };

protected:
    State sampleTarget(const Animation &target) override;

    State sampleRandom() override;
};



#endif //KINODYNAMICBIASEDSAMPLER_H
