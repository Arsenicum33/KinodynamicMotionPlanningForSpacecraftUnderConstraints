// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef ISTATICCOLLISIONHANDLER_H
#define ISTATICCOLLISIONHANDLER_H
#include <components/collisionHandlers/ICollisionHandler.h>

class IStaticCollisionHandler : public ICollisionHandler<Pose>
{
public:
    virtual std::shared_ptr<RAPID_model> getAgent() const = 0;
    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::StaticEnv}; }
};

#endif //ISTATICCOLLISIONHANDLER_H
