//
// Created by arseniy on 12.4.25.
//

#include "AstrodynamicConstraintsEnforcer.h"

std::unique_ptr<IComponent> AstrodynamicConstraintsEnforcer::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    auto kinodynamicEnforcerComponent = KinodynamicConstraintsEnforcer::createComponent(config, context);

    if (auto* castPtr = dynamic_cast<KinodynamicConstraintsEnforcer*>(kinodynamicEnforcerComponent.get()))
    {
        kinodynamicEnforcerComponent.release();
        std::unique_ptr<KinodynamicConstraintsEnforcer> staticHandler(castPtr);
        return std::make_unique<AstrodynamicConstraintsEnforcer>(std::move(staticHandler));
    }
    spdlog::error("Error when creating AstrodynamicConstraintsEnforcer. Provided KinodynamicConstraintsEnforcer is invalid");
    throw std::runtime_error("Error when creating AstrodynamicConstraintsEnforcer. Provided KinodynamicConstraintsEnforcer is invalid");
}

bool AstrodynamicConstraintsEnforcer::satisfiesConstraints(const SpaceshipState &position) const
{
    return kinodynamicConstraintsEnforcer->satisfiesConstraints(position) && (position.getFuel().getMainThrusterFuel() >= 0
        && (position.getFuel().getRotationThrustersFuel() >= 0));
}

void AstrodynamicConstraintsEnforcer::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    IConstraintsEnforcer<SpaceshipState>::resolveDependencies(config, manager);
    kinodynamicConstraintsEnforcer->resolveDependencies(config, manager);
}

