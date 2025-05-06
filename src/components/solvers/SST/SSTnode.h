//
// Created by arseniy on 4.5.25.
//

#ifndef SSTNODE_H
#define SSTNODE_H
#include <memory>
#include <vector>

template <typename StateType>
class SSTnode
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

    double cost = 0.0;
    bool active = true;
};

#endif //SSTNODE_H
