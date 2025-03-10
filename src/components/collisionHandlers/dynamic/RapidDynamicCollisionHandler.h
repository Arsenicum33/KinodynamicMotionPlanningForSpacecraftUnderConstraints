//
// Created by arseniy on 15.1.25.
//

#ifndef RAPIDDYNAMICCOLLISIONHANDLER_H
#define RAPIDDYNAMICCOLLISIONHANDLER_H
#include "IDynamicCollisionHandler.h"


class RapidDynamicCollisionHandler : public IDynamicCollisionHandler
{
public:
    RapidDynamicCollisionHandler(std::shared_ptr<RAPID_model> agent, const std::vector<std::shared_ptr<RAPID_model>>& obstacles,
        const std::vector<std::shared_ptr<DynamicObject<RAPID_model>>>& dynamicObjects) :
        agent(agent), obstacles(obstacles), dynamicObjects(dynamicObjects) {}
    bool isPoseCollisionFree(Pose &pose) const override;

    bool arePosesCollisionFree(std::vector<Pose> &poses, Pose *collidingPose) const override;

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv, Capability::DynamicEnv, Capability::MovingTarget}; }

    bool isKeyframeCollisionFree(Keyframe &keyframe) const override;

    bool areKeyframesCollisionFree(std::vector<Keyframe> &keyframes, Keyframe *collidingKeyframe) const override;

private:
    std::shared_ptr<RAPID_model> agent;
    std::vector<std::shared_ptr<RAPID_model>> obstacles;
    std::vector<std::shared_ptr<DynamicObject<RAPID_model>>> dynamicObjects;
    bool isNotCollidingWithDynamicObjects(Keyframe& keyframe) const;
};



#endif //RAPIDDYNAMICCOLLISIONHANDLER_H
