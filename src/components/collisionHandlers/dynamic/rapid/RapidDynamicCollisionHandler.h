//
// Created by arseniy on 15.1.25.
//

#ifndef RAPIDDYNAMICCOLLISIONHANDLER_H
#define RAPIDDYNAMICCOLLISIONHANDLER_H
#include "components/collisionHandlers/dynamic/IDynamicCollisionHandler.h"


class RapidDynamicCollisionHandler : public IDynamicCollisionHandler
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    RapidDynamicCollisionHandler(std::shared_ptr<RAPID_model> agent, const std::vector<std::shared_ptr<RAPID_model>>& obstacles,
    const std::vector<std::shared_ptr<DynamicObject<RAPID_model>>>& dynamicObjects) :
        agent(agent), obstacles(obstacles), dynamicObjects(dynamicObjects) {}

    bool isPoseCollisionFree(Pose &pose) const override;

    bool arePosesCollisionFree(std::vector<Pose> &poses, Pose *collidingPose) const override;

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv, Capability::DynamicEnv, Capability::MovingTarget}; }

    bool isKeyframeCollisionFree(Keyframe &keyframe) const override;

    bool areKeyframesCollisionFree(std::vector<Keyframe> &keyframes, Keyframe *collidingKeyframe) const override;
protected:

    std::shared_ptr<RAPID_model> agent;
    std::vector<std::shared_ptr<RAPID_model>> obstacles;
    std::vector<std::shared_ptr<DynamicObject<RAPID_model>>> dynamicObjects;
    bool isNotCollidingWithDynamicObjects(Keyframe& keyframe) const;
};



#endif //RAPIDDYNAMICCOLLISIONHANDLER_H
