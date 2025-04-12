//
// Created by arseniy on 8.11.24.
//

#include "UniformPathGenerator.h"


std::unique_ptr<IComponent> UniformPathGenerator::createComponent(const ComponentConfig &config,
                                                                  const ReaderContext &context)
{
    const auto& configMap = config.config;

    double desiredNumberOfFrames = std::any_cast<double>(configMap.at("desiredNumberOfFrames"));

    return std::make_unique<UniformPathGenerator>(desiredNumberOfFrames);
}

std::vector<Pose> UniformPathGenerator::generatePath(std::shared_ptr<const TreeNode<Pose>> goalNode)
{
    std::vector<Pose> keyframes;
    std::shared_ptr<const TreeNode<Pose>> currentNode = goalNode;
    while (currentNode->parent != nullptr)
    {
        keyframes.push_back(currentNode->pose);
        currentNode = currentNode->parent;
    }
    keyframes.push_back(currentNode->pose);
    std::reverse(keyframes.begin(), keyframes.end());

    std::vector<Pose> interpolatedKeyframes;

    for (int i = 0; i < keyframes.size()-1; i++)
    {
        std::vector<Pose> intermediatePoses = interpolator->interpolate(keyframes[i], keyframes[i+1]);
        interpolatedKeyframes.insert(interpolatedKeyframes.end(), intermediatePoses.begin(), intermediatePoses.end()-1);
    }
    interpolatedKeyframes.push_back(goalNode->pose);

    int keyframeFrequency = interpolatedKeyframes.size() / desiredNumberOfFrames;

    std::vector<Pose> resultingFrames;
    for (int i=0; i<interpolatedKeyframes.size(); i+=keyframeFrequency)
    {
        resultingFrames.push_back(interpolatedKeyframes[i]);
    }
    resultingFrames.push_back(goalNode->pose);

    return resultingFrames;
}

void UniformPathGenerator::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    ITreePathGenerator<Pose>::resolveDependencies(config, manager);
    interpolator = std::dynamic_pointer_cast<IInterpolator<Pose>>(manager->getComponent(ComponentType::Interpolator));
}

