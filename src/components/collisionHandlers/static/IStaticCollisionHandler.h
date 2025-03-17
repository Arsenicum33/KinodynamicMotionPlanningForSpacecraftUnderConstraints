//
// Created by arseniy on 17.3.25.
//

#ifndef ISTATICCOLLISIONHANDLER_H
#define ISTATICCOLLISIONHANDLER_H
#include <components/collisionHandlers/ICollisionHandler.h>

class IStaticCollisionHandler : public ICollisionHandler<Pose>
{
public:
    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::StaticEnv}; }
};

#endif //ISTATICCOLLISIONHANDLER_H
