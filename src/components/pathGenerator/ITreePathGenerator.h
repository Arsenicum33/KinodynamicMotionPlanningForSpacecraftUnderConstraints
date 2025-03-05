//
// Created by arseniy on 19.1.25.
//

#ifndef ITREEPATHGENERATOR_H
#define ITREEPATHGENERATOR_H
#include <components/solvers/treeUtils/TreeNode.h>
#include "IPathGenerator.h"

template <typename T>
class ITreePathGenerator  : public IPathGenerator
{
public:

    virtual std::vector<T> generatePath(std::shared_ptr<TreeNode<T>> finalNode) = 0;
};


#endif //ITREEPATHGENERATOR_H
