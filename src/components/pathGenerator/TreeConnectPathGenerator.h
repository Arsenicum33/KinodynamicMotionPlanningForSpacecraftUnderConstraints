//
// Created by arseniy on 19.1.25.
//

#ifndef TREECONNECTPATHGENERATOR_H
#define TREECONNECTPATHGENERATOR_H
#include "ITreeConnectPathGenerator.h"


class TreeConnectPathGenerator : public ITreeConnectPathGenerator
{
public:
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::DynamicEnv}; };

    std::vector<Keyframe> generatePath(std::shared_ptr<TreeNode<Keyframe>> startTreeConnectionNode,
        std::shared_ptr<TreeNode<Keyframe>> goalTreeConnectionNode) override;
};



#endif //TREECONNECTPATHGENERATOR_H
