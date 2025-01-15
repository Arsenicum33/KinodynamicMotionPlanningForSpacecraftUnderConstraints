//
// Created by arseniy on 15.1.25.
//

#ifndef ICOSTFUNCTION_H
#define ICOSTFUNCTION_H
#include <components/solvers/treeSolvers/TreeNode.h>

#include "components/IComponent.h"

template<typename T>
class ICostFunction : public IComponent
{
public:
    virtual void apply(const TreeNode<T>& nearestNode, TreeNode<T>& newNode) = 0;
};

#endif //ICOSTFUNCTION_H
