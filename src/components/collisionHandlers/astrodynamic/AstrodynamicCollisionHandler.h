//
// Created by arseniy on 11.4.25.
//

#ifndef ASTRODYNAMICCOLLISIONHANDLER_H
#define ASTRODYNAMICCOLLISIONHANDLER_H
#include <components/collisionHandlers/ICollisionHandler.h>

#include "dto/poses/astrodynamic/celestialBody/CelestialBody.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"


class AstrodynamicCollisionHandler : public ICollisionHandler<SpaceshipState>
{
public:
    AstrodynamicCollisionHandler(std::vector<CelestialBody> celestialBodies) {}
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::AstrodynamicEnv}; };

    bool isCollisionFree(SpaceshipState &position) const override;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

private:
    std::vector<CelestialBody> celestialBodies;
    std::shared_ptr<IDistanceMetric> distanceMetric;
};



#endif //ASTRODYNAMICCOLLISIONHANDLER_H
