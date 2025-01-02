//
// Created by arseniy on 30.10.24.
//

#ifndef ICOLLISIONHANDLER_H
#define ICOLLISIONHANDLER_H
#include "../poses/static/Pose.h"

class ICollisionHandler
{
public:
    virtual ~ICollisionHandler() = default;
    virtual bool isPoseCollisionFree(Pose& pose) const = 0;
    virtual bool arePosesCollisionFree(std::vector<Pose>& poses) const = 0;
};

#endif //ICOLLISIONHANDLER_H
