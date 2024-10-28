//
// Created by arseniy on 28.10.24.
//

#ifndef BIASEDRANDOMSAMPLER_H
#define BIASEDRANDOMSAMPLER_H
#include "DefaultRandomSampler.h"


class BiasedRandomSampler : public DefaultRandomSampler
{
public:
    BiasedRandomSampler(ConfigurationSpaceBoundaries boundaries, double goalBias, Pose goalPose) :
    DefaultRandomSampler(std::move(boundaries)), goalBias(goalBias), goalPose(std::move(goalPose))
    { if (goalBias < 0.0 || goalBias > 1.0) { throw std::runtime_error("BiasedRandomSampler: Invalid goal bias value"); }}
    Pose samplePose() override;

private:
    const double goalBias;
    const Pose goalPose;
};



#endif //BIASEDRANDOMSAMPLER_H
