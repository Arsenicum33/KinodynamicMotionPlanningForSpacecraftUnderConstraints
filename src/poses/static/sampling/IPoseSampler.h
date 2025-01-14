//
// Created by arseniy on 28.10.24.
//

#ifndef IPOSESAMPLER_H
#define IPOSESAMPLER_H

#include "../Pose.h"
#include "components/IComponent.h"

class IPoseSampler : public IComponent
{
public:
    virtual Pose samplePose() = 0;


};

#endif //IPOSESAMPLER_H
