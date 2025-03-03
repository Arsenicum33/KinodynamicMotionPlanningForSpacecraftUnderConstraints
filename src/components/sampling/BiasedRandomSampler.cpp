//
// Created by arseniy on 28.10.24.
//

#include "BiasedRandomSampler.h"

Pose BiasedRandomSampler::samplePose()
{
    if (std::generate_canonical<double, 10>(gen) < goalBias)
        return goalPose;
    return DefaultRandomSampler::samplePose();
}
