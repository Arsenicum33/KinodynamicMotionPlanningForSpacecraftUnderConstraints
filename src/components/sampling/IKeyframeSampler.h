//
// Created by arseniy on 15.1.25.
//

#ifndef IKEYFRAMESAMPLER_H
#define IKEYFRAMESAMPLER_H
#include "ISampler.h"


class IKeyframeSampler : public ISampler<Keyframe>
{
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::DynamicEnv};}
};



#endif //IKEYFRAMESAMPLER_H
