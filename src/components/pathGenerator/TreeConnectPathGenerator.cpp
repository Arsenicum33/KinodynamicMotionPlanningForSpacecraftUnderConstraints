//
// Created by arseniy on 19.1.25.
//

#include "TreeConnectPathGenerator.h"

#include <poses/static/PoseMath.h>

#include "poses/dynamic/KeyframeMath.h"

std::vector<Keyframe> TreeConnectPathGenerator::generatePath(
    std::shared_ptr<TreeNode<Keyframe>> startTreeConnectionNode,
    std::shared_ptr<TreeNode<Keyframe>> goalTreeConnectionNode)
{
    std::vector<Keyframe> keyframesStart;
    std::vector<Keyframe> keyframesGoal;
    std::shared_ptr<TreeNode<Keyframe>> currentNode = startTreeConnectionNode;
    while (currentNode->parent != nullptr)
    {
        keyframesStart.push_back(currentNode->pose);
        currentNode = currentNode->parent;
    }
    keyframesStart.push_back(currentNode->pose);
    std::reverse(keyframesStart.begin(), keyframesStart.end());

    std::vector<Keyframe> waitingFrames = KeyframeMath::interpolateKeyframes(keyframesStart[keyframesStart.size()-1], goalTreeConnectionNode->pose, 0.1, 0.1);
    keyframesStart.insert(keyframesStart.end(), waitingFrames.begin(), waitingFrames.end());

    currentNode = goalTreeConnectionNode;
    while (currentNode->parent != nullptr)
    {
        keyframesGoal.push_back(currentNode->pose);
        currentNode = currentNode->parent;
    }
    keyframesGoal.push_back(currentNode->pose);
    keyframesStart.insert(keyframesStart.end(), keyframesGoal.begin(), keyframesGoal.end());
    return keyframesStart;
}
