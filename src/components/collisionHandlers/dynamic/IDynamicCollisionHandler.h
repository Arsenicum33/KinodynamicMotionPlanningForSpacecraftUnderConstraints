//
// Created by arseniy on 15.1.25.
//

#ifndef IDYNAMICCOLLISIONHANDLER_H
#define IDYNAMICCOLLISIONHANDLER_H
#include <components/collisionHandlers/ICollisionHandler.h>


class IDynamicCollisionHandler : public ICollisionHandler
{
public:
    virtual bool isKeyframeCollisionFree(Keyframe& pose) const = 0;
    virtual bool areKeyframesCollisionFree(std::vector<Keyframe>& keyframes) const = 0;
};
#endif //IDYNAMICCOLLISIONHANDLER_H
