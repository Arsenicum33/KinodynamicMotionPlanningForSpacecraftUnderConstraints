//
// Created by arseniy on 28.10.24.
//

#include "BiasedRandomSampler.h"

Pose BiasedRandomSampler::samplePose(Pose target)
{
    if (std::generate_canonical<double, 10>(gen) < goalBias)
        return target;
    return DefaultRandomSampler::samplePose(target);
}
