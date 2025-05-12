//
// Created by arseniy on 11.5.25.
//

#ifndef AMPNN_RRT_H
#define AMPNN_RRT_H
#include <components/nearestNeighbour/mpnn/AMPNNsearch.h>
#include <components/solvers/RRT/treeUtils/TreeNode.h>

template <typename StateType, typename SearchedType>
class AMPNN_RRT : public AMPNNsearch<TreeNode<StateType>, SearchedType>
{
public:
    explicit AMPNN_RRT(int maxNeighbours)
        : AMPNNsearch<TreeNode<StateType>, SearchedType>(maxNeighbours)
    {
    }
};

#endif //AMPNN_RRT_H
