//
// Created by arseniy on 15.1.25.
//

#ifndef KEYFRAMEMATH_H
#define KEYFRAMEMATH_H
#include <vector>

#include "DynamicObject.h"
#include "Keyframe.h"


class KeyframeMath
{
public:
    static Keyframe getKeyframeAtTime(DynamicObject<RAPID_model>* dynamicObject, double time);
    static std::vector<Keyframe> interpolateKeyframes(const Keyframe &start, const Keyframe &end, double interpolationThreshold, double rotationThreshold);
    static std::vector<Keyframe> getKeyframesAtDiscreteTimes(const std::vector<Keyframe>& keyframes);
    static std::vector<Keyframe> getInterpolatedKeyframesAtRate(const std::vector<Keyframe>& keyframes, int fps);
private:
    static Keyframe getInterpolatedKeyframeAtTime(const Keyframe& before,const Keyframe& after, double time);
};



#endif //KEYFRAMEMATH_H
