// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


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
