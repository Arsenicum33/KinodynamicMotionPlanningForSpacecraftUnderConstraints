//
// Created by arseniy on 30.10.24.
//

#ifndef ICOLLISIONHANDLER_H
#define ICOLLISIONHANDLER_H
#include <components/interpolators/IInterpolator.h>

#include "components/IComponent.h"

template <typename PositionType>
class ICollisionHandler : public IComponent
{
public:
    virtual bool isCollisionFree(PositionType& position) const = 0;
    bool isTransitionValid(const PositionType& from, const PositionType& to) const;
    bool areCollisionFree(std::vector<PositionType>& positions, PositionType* collidingPosition = nullptr) const;
    virtual std::shared_ptr<RAPID_model> getAgent() const = 0;
    ComponentType getType() const override { return ComponentType::CollisionHandler; }

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

private:
    std::shared_ptr<IInterpolator<PositionType>> interpolator;
};

template<typename PositionType>
bool ICollisionHandler<PositionType>::isTransitionValid(const PositionType &from, const PositionType &to) const
{
    std::vector<PositionType> interpolatedTransition = interpolator->interpolate(from, to);
    return areCollisionFree(interpolatedTransition);
}

template<typename PositionType>
bool ICollisionHandler<PositionType>::areCollisionFree(std::vector<PositionType> &positions,
    PositionType *collidingPosition) const
{
    for (PositionType& position :  positions)
    {
        if (isCollisionFree(position))
            continue;
        if (collidingPosition != nullptr)
            *collidingPosition = position;
        return false;
    }
    return true;
}

template<typename PositionType>
void ICollisionHandler<PositionType>::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    IComponent::resolveDependencies(config, manager);
    interpolator = std::dynamic_pointer_cast<IInterpolator<PositionType>>(manager->getComponent(ComponentType::Interpolator));
}

#endif //ICOLLISIONHANDLER_H
