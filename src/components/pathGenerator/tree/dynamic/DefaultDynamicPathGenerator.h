//
// Created by arseniy on 17.1.25.
//

#ifndef DEFAULTDYNAMICPATHGENERATOR_H
#define DEFAULTDYNAMICPATHGENERATOR_H
#include "components/pathGenerator/tree/ITreePathGenerator.h"


class DefaultDynamicPathGenerator : public ITreePathGenerator<Keyframe>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv, Capability::DynamicEnv, Capability::MovingTarget}; }

    std::vector<Keyframe> generatePath(std::shared_ptr<TreeNode<Keyframe>> goalNode) override;
};



#endif //DEFAULTDYNAMICPATHGENERATOR_H
