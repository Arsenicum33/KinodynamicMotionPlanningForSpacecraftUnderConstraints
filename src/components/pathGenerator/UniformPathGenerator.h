//
// Created by arseniy on 8.11.24.
//

#ifndef UNIFORMPATHGENERATOR_H
#define UNIFORMPATHGENERATOR_H
#include "IPathGenerator.h"


class UniformPathGenerator : public IPathGenerator<Pose>
{
public:
    UniformPathGenerator(double interpolationThreshold, double interpolationRotationThreshold, int desiredNumberOfFrames) :
    interpolationThreshold(interpolationThreshold), interpolationRotationThreshold(interpolationRotationThreshold),
    desiredNumberOfFrames(desiredNumberOfFrames) {}

    std::vector<Pose> generatePath(std::shared_ptr<TreeNode<Pose>> goalNode) override;
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv}; }

    void resolveDependencies(ComponentConfig &config, ComponentManager *manager) override;;
private:
    double interpolationThreshold;
    double interpolationRotationThreshold;
    int desiredNumberOfFrames;
};



#endif //UNIFORMPATHGENERATOR_H
