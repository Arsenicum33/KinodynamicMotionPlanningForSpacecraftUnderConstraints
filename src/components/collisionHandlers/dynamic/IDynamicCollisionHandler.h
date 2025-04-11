//
// Created by arseniy on 15.1.25.
//

#ifndef IDYNAMICCOLLISIONHANDLER_H
#define IDYNAMICCOLLISIONHANDLER_H
#include <components/collisionHandlers/ICollisionHandler.h>


class IDynamicCollisionHandler : public ICollisionHandler<Keyframe>
{
public:
    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::DynamicEnv, Capability::MovingTarget}; }
    virtual std::shared_ptr<RAPID_model> getAgent() const = 0;
};

#endif //IDYNAMICCOLLISIONHANDLER_H
