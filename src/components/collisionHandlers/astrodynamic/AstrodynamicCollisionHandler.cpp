//
// Created by arseniy on 11.4.25.
//

#include "AstrodynamicCollisionHandler.h"

#include <utils/AnimationUtils.h>

#include "dto/envSettings/EnvSettingsAstro.h"

std::unique_ptr<IComponent> AstrodynamicCollisionHandler::createComponent(const ComponentConfig &config,
                                                                          const ReaderContext &context)
{
    const EnvSettingsAstro* envSettings = dynamic_cast<const EnvSettingsAstro*>(context.envSettings.get());
    return std::make_unique<AstrodynamicCollisionHandler>(envSettings->celestialBodies);
}

bool AstrodynamicCollisionHandler::isCollisionFree(SpaceshipState &position) const
{
    for (const auto &celestialBody : celestialBodies)
    {
        double distance = distanceMetric->getSpatialDistance(position,
            AnimationUtils::extractKeyframeAtTime(celestialBody.getAnimation(), position.time));
        if (distance < celestialBody.getRadius())
            return false;
    }
    return true;
}

void AstrodynamicCollisionHandler::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    ICollisionHandler<SpaceshipState>::resolveDependencies(config, manager);
    distanceMetric = std::dynamic_pointer_cast<IDistanceMetric>(manager->getComponent(ComponentType::DistanceMetric));
}
