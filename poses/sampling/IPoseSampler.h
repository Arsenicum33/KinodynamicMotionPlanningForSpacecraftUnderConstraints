//
// Created by arseniy on 28.10.24.
//

#ifndef IPOSESAMPLER_H
#define IPOSESAMPLER_H

#include "../Pose.h"
#include "../../ConfigurationSpaceBoundaries.h"
#include <optional>

class IPoseSampler
{
public:
    virtual ~IPoseSampler() = default;
    virtual Pose samplePose() = 0;
};

#endif //IPOSESAMPLER_H
