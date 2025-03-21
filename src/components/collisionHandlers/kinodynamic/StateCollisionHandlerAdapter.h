//
// Created by arseniy on 21.3.25.
//

#ifndef STATECOLLISIONHANDLERADAPTER_H
#define STATECOLLISIONHANDLERADAPTER_H
#include <components/collisionHandlers/ICollisionHandler.h>

#include "components/collisionHandlers/dynamic/DynamicCollisionHandler.h"
#include "dto/poses/dynamic/kinodynamic/state/State.h"

class StateCollisionHandlerAdapter : public ICollisionHandler<State>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context)
    {
        auto keyframeHandlerComponent = DynamicCollisionHandler::createComponent(config, context);

        if (auto* castPtr = dynamic_cast<IDynamicCollisionHandler*>(keyframeHandlerComponent.get()))
        {
            keyframeHandlerComponent.release();
            std::unique_ptr<IDynamicCollisionHandler> dynamicCollisionHandler(castPtr);
            return std::make_unique<StateCollisionHandlerAdapter>(std::move(dynamicCollisionHandler));
        }
        spdlog::error("Error when creating StateCollisionHandlerAdapter. Provided DynamicCollisionHandler is invalid");
        throw std::runtime_error("Error when creating StateCollisionHandlerAdapter. Provided DynamicCollisionHandler is invalid");
    }

    StateCollisionHandlerAdapter(std::unique_ptr<IDynamicCollisionHandler> keyframeCollisionHandler) :
        keyframeCollisionHandler(std::move(keyframeCollisionHandler)) {}

    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::KinodynamicEnv}; }

    bool isCollisionFree(State &position) const override { return keyframeCollisionHandler->isCollisionFree(position); }

    std::shared_ptr<RAPID_model> getAgent() const override { return keyframeCollisionHandler->getAgent(); }

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override { keyframeCollisionHandler->resolveDependencies(config, manager); }

private:
    std::unique_ptr<IDynamicCollisionHandler> keyframeCollisionHandler;

};

#endif //STATECOLLISIONHANDLERADAPTER_H
