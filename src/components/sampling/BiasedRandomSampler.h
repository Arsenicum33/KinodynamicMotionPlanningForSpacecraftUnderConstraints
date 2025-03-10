//
// Created by arseniy on 28.10.24.
//

#ifndef BIASEDRANDOMSAMPLER_H
#define BIASEDRANDOMSAMPLER_H
#include <spdlog/spdlog.h>

#include "DefaultRandomSampler.h"


class BiasedRandomSampler : public DefaultRandomSampler
{
public:
    BiasedRandomSampler(ConfigurationSpaceBoundaries boundaries, double goalBias) :
    DefaultRandomSampler(std::move(boundaries)), goalBias(goalBias)
    {
        if (goalBias < 0.0 || goalBias > 1.0)
        {
            spdlog::error("Goal bias must be between 0.0 and 1.0");
            throw std::runtime_error("BiasedRandomSampler: Invalid goal bias value");
        }
    }
    Pose samplePose(Pose target) override;

private:
    const double goalBias;
};



#endif //BIASEDRANDOMSAMPLER_H
