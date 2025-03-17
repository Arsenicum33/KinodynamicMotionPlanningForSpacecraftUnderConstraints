//
// Created by arseniy on 14.3.25.
//

#ifndef IKEYFRAMEINTERPOLATOR_H
#define IKEYFRAMEINTERPOLATOR_H
#include "components/interpolators/IInterpolator.h"

class IKeyframeInterpolator : public IInterpolator<Keyframe>
{
public:
    virtual std::vector<Keyframe> getInterpolatedKeyframesAtRate(const std::vector<Keyframe>& keyframes, int fps) = 0;
    virtual Keyframe getInterpolatedKeyframeAtTime(const Keyframe& before,const Keyframe& after, double time) = 0;
    virtual Keyframe extractKeyframeAtTime(DynamicObject<RAPID_model>* dynamicObject, double time) = 0;
};

#endif //IKEYFRAMEINTERPOLATOR_H
