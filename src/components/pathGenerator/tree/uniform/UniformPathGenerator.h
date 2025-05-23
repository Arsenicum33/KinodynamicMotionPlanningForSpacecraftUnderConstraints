// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef UNIFORMPATHGENERATOR_H
#define UNIFORMPATHGENERATOR_H
#include "components/interpolators/IInterpolator.h"
#include "components/pathGenerator/tree/ITreePathGenerator.h"


class UniformPathGenerator : public ITreePathGenerator<Pose>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    UniformPathGenerator(int desiredNumberOfFrames) :
                         desiredNumberOfFrames(desiredNumberOfFrames) {}

    std::vector<Pose> generatePath(std::shared_ptr<const TreeNode<Pose>> goalNode) override;
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv}; }

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

private:
    int desiredNumberOfFrames;
    std::shared_ptr<IInterpolator<Pose>> interpolator;
};



#endif //UNIFORMPATHGENERATOR_H
