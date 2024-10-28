//
// Created by arseniy on 23.10.24.
//

#ifndef TREENODE_H
#define TREENODE_H

#include "../../poses/Pose.h"

class TreeNode
{
public:
    Pose pose;
    std::shared_ptr<TreeNode> parent;
    // std::vector<std::shared_ptr<TreeNode>> children;
    TreeNode(const Pose& pose, const std::shared_ptr<TreeNode> &parentNode = nullptr)
        : pose(pose), parent(parentNode) {}
};


#endif //TREENODE_H
