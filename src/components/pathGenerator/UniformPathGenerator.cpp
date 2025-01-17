//
// Created by arseniy on 8.11.24.
//

#include "UniformPathGenerator.h"

#include "../../poses/static/PoseMath.h"

std::vector<Pose> UniformPathGenerator::generatePath(std::shared_ptr<TreeNode<Pose>> goalNode)
{
    std::vector<Pose> keyframes;
    std::shared_ptr<TreeNode<Pose>> currentNode = goalNode;
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
        std::vector<Pose> intermediatePoses = PoseMath::interpolatePoses(keyframes[i], keyframes[i+1],
                                                                            interpolationThreshold, interpolationRotationThreshold);
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

