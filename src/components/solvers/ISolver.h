//
// Created by arseniy on 16.3.25.
//

#ifndef ISOLVER_H
#define ISOLVER_H
#include "components/IComponent.h"
#include "RRT/treeUtils/ANode.h"

class ISolver : public IComponent
{
public:
    ComponentType getType() const override { return ComponentType::Solver; };

    virtual std::vector<std::any> solve(const std::any& start, const std::any& target) = 0;
    virtual std::vector<std::shared_ptr<ANode>> getData() = 0;

    virtual int getTotalRuntime() const = 0;
    virtual int getTotalIterations() const = 0;
};

#endif //ISOLVER_H
