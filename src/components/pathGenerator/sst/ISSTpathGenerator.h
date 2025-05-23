// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef ISSTPATHGENERATOR_H
#define ISSTPATHGENERATOR_H
#include <components/pathGenerator/IPathGenerator.h>

#include "components/solvers/SST/SSTnode.h"

template <typename StateType>
class ISSTpathGenerator : public IPathGenerator
{
public:
    virtual std::vector<StateType> generatePath(std::shared_ptr<SSTnode<StateType>> finalNode);
};

template<typename StateType>
std::vector<StateType> ISSTpathGenerator<StateType>::generatePath(std::shared_ptr<SSTnode<StateType>> finalNode)
{
    std::vector<StateType> result;
    std::shared_ptr<SSTnode<StateType>>& currentNode = finalNode;
    while (!currentNode->parent.expired())
    {
        result.push_back(currentNode->state);
        currentNode = currentNode->parent.lock();
    }
    result.push_back(currentNode->state);
    std::reverse(result.begin(), result.end());
    return result;
}

#endif //ISSTPATHGENERATOR_H
