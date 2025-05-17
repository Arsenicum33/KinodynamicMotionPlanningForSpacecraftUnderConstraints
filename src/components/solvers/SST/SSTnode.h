//
// Created by arseniy on 4.5.25.
//

#ifndef SSTNODE_H
#define SSTNODE_H
#include <memory>
#include <vector>

#include "components/solvers/RRT/treeUtils/ANode.h"

template <typename StateType>
class SSTnode : public ANode
{
public:
    SSTnode(const StateType& state, double cost,
            std::weak_ptr<SSTnode<StateType>> parent = std::weak_ptr<SSTnode<StateType>>())
        : state(state), cost(cost), parent(parent) {}

    StateType state;
    std::weak_ptr<SSTnode> parent;
    std::vector<std::shared_ptr<SSTnode>> children;

    void removeChild(std::shared_ptr<SSTnode> child)
    {
        auto it = std::find(children.begin(), children.end(), child);
        if (it != children.end()) {
            children.erase(it);
        }
    }

    std::weak_ptr<ANode> getParent() override { return parent; };

    std::vector<std::shared_ptr<ANode>> getChildren() override;

    const Pose * getStateRepresentation() const override;

    double cost = 0.0;
    bool active = true;
};

template<typename StateType>
std::vector<std::shared_ptr<ANode>> SSTnode<StateType>::getChildren()
{
    std::vector<std::shared_ptr<ANode>> result;
    for (auto child : children)
    {
        result.push_back(child);
    }
    return result;
}

template<typename StateType>
const Pose * SSTnode<StateType>::getStateRepresentation() const
{
    return &state;
}

#endif //SSTNODE_H
