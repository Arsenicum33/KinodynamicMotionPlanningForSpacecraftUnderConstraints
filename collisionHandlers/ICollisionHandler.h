//
// Created by arseniy on 30.10.24.
//

#ifndef ICOLLISIONHANDLER_H
#define ICOLLISIONHANDLER_H
#include "../poses/Pose.h"

class ICollisionHandler
{
public:
    virtual ~ICollisionHandler() = default;
    virtual bool isPoseCollisionFree(Pose& pose) = 0;
    virtual bool arePosesCollisionFree(std::vector<Pose>& poses) = 0;
};

#endif //ICOLLISIONHANDLER_H
