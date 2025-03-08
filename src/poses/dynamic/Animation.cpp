//
// Created by arseniy on 2.1.25.
//

#include "Animation.h"

#include <spdlog/spdlog.h>

#include "KeyframeMath.h"

Keyframe Animation::getKeyframeAtTime(double time) const
{
    if (cyclic)
    {
        spdlog::error("Cyclic animations not yet supported");
        throw std::runtime_error("KeyframeMath::getKeyframeAtTime: Keyframe cycle not implemented");
    }
    for (int i=1;i<keyframes.size(); i++)
    {
        if (keyframes[i].time >= time)
        {
            const Keyframe& beforeTime = keyframes[i-1];
            const Keyframe& afterTime = keyframes[i];
            return KeyframeMath::getInterpolatedKeyframeAtTime(beforeTime, afterTime, time);
        }
    }
    Keyframe lastKeyframe = keyframes[keyframes.size()-1];
    return Keyframe(lastKeyframe.translation, lastKeyframe.rotation, time);
}
