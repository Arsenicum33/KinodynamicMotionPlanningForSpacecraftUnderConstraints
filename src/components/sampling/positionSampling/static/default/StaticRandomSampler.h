//
// Created by arseniy on 18.3.25.
//

#ifndef STATICDEFAULTRANDOMSAMPLER_H
#define STATICDEFAULTRANDOMSAMPLER_H
#include "../../ARandomSampler.h"


class StaticRandomSampler : public ARandomSampler<Pose, Pose>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    explicit StaticRandomSampler(const ConfigurationSpaceBoundaries &boundaries)
        : ARandomSampler<Pose, Pose>(boundaries) {}

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv}; }

    Pose sample(Pose target) override;
};



#endif //STATICDEFAULTRANDOMSAMPLER_H
