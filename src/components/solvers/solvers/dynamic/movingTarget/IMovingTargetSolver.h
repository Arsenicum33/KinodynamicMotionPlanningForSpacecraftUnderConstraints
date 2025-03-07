//
// Created by arseniy on 7.3.25.
//

#ifndef IMOVINGTARGETSOLVER_H
#define IMOVINGTARGETSOLVER_H
#include <vector>
#include <poses/dynamic/Animation.h>
#include <poses/dynamic/Keyframe.h>

class IMovingTargetSolver
{
public:
    virtual ~IMovingTargetSolver() = default;

    virtual std::vector<Keyframe> solve(const Pose& startPosition, const Animation& target) = 0;
};
#endif //IMOVINGTARGETSOLVER_H
