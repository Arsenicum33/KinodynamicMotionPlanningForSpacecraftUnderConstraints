//
// Created by arseniy on 17.1.25.
//

#include "DefaultDynamicPathGenerator.h"

std::unique_ptr<IComponent> DefaultDynamicPathGenerator::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    return std::make_unique<DefaultDynamicPathGenerator>();
}

std::vector<Keyframe> DefaultDynamicPathGenerator::generatePath(std::shared_ptr<const TreeNode<Keyframe>> goalNode)
{
    std::vector<Keyframe> keyframes;
    std::shared_ptr<const TreeNode<Keyframe>> currentNode = goalNode;
    while (currentNode->parent != nullptr)
    {
        keyframes.push_back(currentNode->pose);
        currentNode = currentNode->parent;
    }
    keyframes.push_back(currentNode->pose);
    std::reverse(keyframes.begin(), keyframes.end());
    return keyframes;
}
