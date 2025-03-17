//
// Created by arseniy on 17.3.25.
//

#ifndef DYNAMICCOLLISIONHANDLER_H
#define DYNAMICCOLLISIONHANDLER_H
#include "IDynamicCollisionHandler.h"
#include "components/collisionHandlers/static/IStaticCollisionHandler.h"
#include "components/interpolators/keyframe/IKeyframeInterpolator.h"


class DynamicCollisionHandler : public IDynamicCollisionHandler
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    DynamicCollisionHandler(std::unique_ptr<IStaticCollisionHandler> staticCollisionHandler,
        const std::vector<std::shared_ptr<DynamicObject<RAPID_model>>>& dynamicObjects) :
            staticHandler(std::move(staticCollisionHandler)),dynamicObjects(dynamicObjects) {};
    bool isCollisionFree(Keyframe &position) const override;
protected:
    std::unique_ptr<IStaticCollisionHandler> staticHandler;
    std::vector<std::shared_ptr<DynamicObject<RAPID_model>>> dynamicObjects;
    std::shared_ptr<IKeyframeInterpolator> interpolator;
private:
    bool isNotCollidingWithDynamicObjects(Keyframe& keyframe) const;

public:
    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

    std::shared_ptr<RAPID_model> getAgent() const override { return staticHandler->getAgent(); };
};



#endif //DYNAMICCOLLISIONHANDLER_H
