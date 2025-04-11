//
// Created by arseniy on 11.4.25.
//

#include "AstrodynamicTerminationCondition.h"

std::unique_ptr<IComponent> AstrodynamicTerminationCondition::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    auto kinodynamicComponent = KinodynamicTerminationCondition::createComponent(config, context);

    if (auto* castPtr = dynamic_cast<KinodynamicTerminationCondition*>(kinodynamicComponent.get()))
    {
        kinodynamicComponent.release();
        std::unique_ptr<KinodynamicTerminationCondition> kinodynamicHandler(castPtr);
        return std::make_unique<AstrodynamicTerminationCondition>(std::move(kinodynamicHandler));
    }
    spdlog::error("Error when creating DynamicCollisionHandler. Provided IStaticCollisionHandler is invalid");
    throw std::runtime_error("Error when creating DynamicCollisionHandler. Provided IStaticCollisionHandler is invalid");
}

bool AstrodynamicTerminationCondition::isTargetReached(const SpaceshipState &currentPosition,
                                                       const CelestialBody &target)
{
    return terminationCondition->isTargetReached(currentPosition, *(target.getAnimation()));
}

void AstrodynamicTerminationCondition::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    ITerminationCondition<SpaceshipState, CelestialBody>::resolveDependencies(config, manager);
    terminationCondition->resolveDependencies(config, manager);
}
