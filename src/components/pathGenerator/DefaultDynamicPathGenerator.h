//
// Created by arseniy on 17.1.25.
//

#ifndef DEFAULTDYNAMICPATHGENERATOR_H
#define DEFAULTDYNAMICPATHGENERATOR_H
#include "IPathGenerator.h"


class DefaultDynamicPathGenerator : public IPathGenerator<Keyframe>
{
public:
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::DynamicEnv}; }

    std::vector<Keyframe> generatePath(std::shared_ptr<TreeNode<Keyframe>> goalNode) override;
};



#endif //DEFAULTDYNAMICPATHGENERATOR_H
