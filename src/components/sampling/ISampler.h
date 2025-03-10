//
// Created by arseniy on 28.10.24.
//

#ifndef ISAMPLER_H
#define ISAMPLER_H

#include "poses/static/Pose.h"
#include "components/IComponent.h"

template <typename R, typename T>
class ISampler : public IComponent
{
public:
    std::string getName() const override { return "Sampler"; };
    virtual R samplePose(T target) = 0;


};

#endif //ISAMPLER_H
