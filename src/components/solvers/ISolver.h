// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


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

    int getTotalNodes() { return totalNodes; }
    std::vector<std::pair<int, int>> getIterationsToNodes() { return iterationsToNodes; }
    std::vector<std::pair<int, double>> getIterationsToRuntime() { return iterationsToRuntime; }

protected:
    int totalNodes=0;
    int dataOutputPeriod = 1000;
    std::vector<std::pair<int, int>> iterationsToNodes { std::pair<int,int>{0, 1}};
    std::vector<std::pair<int, double>> iterationsToRuntime { };
};

#endif //ISOLVER_H
