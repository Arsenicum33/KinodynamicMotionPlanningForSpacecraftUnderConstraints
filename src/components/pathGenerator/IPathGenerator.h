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

template <typename T>
class IPathGenerator  : public IComponent
{
public:
    virtual std::vector<T> generatePath(std::shared_ptr<TreeNode<T>> finalNode) = 0;
};

#endif //IPATHGENERATOR_H
