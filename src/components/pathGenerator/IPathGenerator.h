//
// Created by arseniy on 8.11.24.
//

#ifndef IPATHGENERATOR_H
#define IPATHGENERATOR_H
#include <memory>
#include <vector>

#include "../../poses/static/Pose.h"
#include "../solvers/treeSolvers/TreeNode.h"
#include "components/IComponent.h"

class IPathGenerator  : public IComponent
{
    std::string getName() const override { return "PathGenerator"; };
};

#endif //IPATHGENERATOR_H
