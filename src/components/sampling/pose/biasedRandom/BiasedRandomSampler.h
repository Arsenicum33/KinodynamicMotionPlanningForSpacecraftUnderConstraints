//
// Created by arseniy on 28.10.24.
//

#ifndef BIASEDRANDOMSAMPLER_H
#define BIASEDRANDOMSAMPLER_H
#include <spdlog/spdlog.h>

#include "components/sampling/pose/defaultRandom/DefaultRandomSampler.h"


class BiasedRandomSampler : public DefaultRandomSampler
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    BiasedRandomSampler(ConfigurationSpaceBoundaries boundaries, double goalBias) :
        DefaultRandomSampler(std::move(boundaries)), goalBias(goalBias) { validateConstructorParams(); }

    Pose samplePose(Pose target) override;
private:
    const double goalBias;
    void validateConstructorParams();
};



#endif //BIASEDRANDOMSAMPLER_H
