// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef STATICCOLLISIONHANDLER_H
#define STATICCOLLISIONHANDLER_H
#include <components/collisionHandlers/ICollisionHandler.h>

#include "IStaticCollisionHandler.h"


class StaticCollisionHandler : public IStaticCollisionHandler
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    StaticCollisionHandler(std::shared_ptr<RAPID_model> agent, const std::vector<std::shared_ptr<RAPID_model>>& obstacles) : //TODO maybe modify ownership of obstacles
    agent(agent), obstacles(obstacles) {}

    bool isCollisionFree(Pose &position) const override;

    std::shared_ptr<RAPID_model> getAgent() const override { return agent; };

private:
    std::shared_ptr<RAPID_model> agent;
    std::vector<std::shared_ptr<RAPID_model>> obstacles;
};



#endif //STATICCOLLISIONHANDLER_H
