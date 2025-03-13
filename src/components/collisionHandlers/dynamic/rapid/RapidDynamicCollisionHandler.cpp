//
// Created by arseniy on 15.1.25.
//

#include "RapidDynamicCollisionHandler.h"

#include "poses/dynamic/KeyframeMath.h"

bool RapidDynamicCollisionHandler::isPoseCollisionFree(Pose &pose) const
{
    std::array<double, 3> zero_transaltion = {0, 0, 0};
    double zero_rotation[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};

    for (auto& obstacle : obstacles)
    {
        RAPID_Collide(pose.rotation, pose.translation.data(), agent.get(), zero_rotation, zero_transaltion.data(), obstacle.get());
        if (RAPID_num_contacts > 0)
            return false;
    }

    return true;
}

bool RapidDynamicCollisionHandler::arePosesCollisionFree(std::vector<Pose> &poses, Pose *collidingPose) const
{
    for (Pose& pose : poses)
    {
        if (!isPoseCollisionFree(pose))
        {
            collidingPose = &pose;
            return false;
        }
    }
    return true;
}

bool RapidDynamicCollisionHandler::isKeyframeCollisionFree(Keyframe &keyframe) const
{
    return isPoseCollisionFree(keyframe) && isNotCollidingWithDynamicObjects(keyframe);
}

bool RapidDynamicCollisionHandler::areKeyframesCollisionFree(std::vector<Keyframe> &keyframes, Keyframe *collidingKeyframe) const
{
    for (Keyframe& keyframe : keyframes)
    {
        if (!isKeyframeCollisionFree(keyframe))
        {
            collidingKeyframe = &keyframe;
            return false;
        }

    }
    return true;
}


bool RapidDynamicCollisionHandler::isNotCollidingWithDynamicObjects(Keyframe& keyframe) const
{
    double time = keyframe.time;
    for (auto& dynamicObject : dynamicObjects)
    {
        Keyframe dynamicObjectKeyframe = KeyframeMath::getKeyframeAtTime(dynamicObject.get(), time);
        RAPID_Collide(keyframe.rotation, keyframe.translation.data(), agent.get(),
                        dynamicObjectKeyframe.rotation, dynamicObjectKeyframe.translation.data(), dynamicObject->getMesh());
        if (RAPID_num_contacts > 0)
            return false;
    }
    return true;
}




