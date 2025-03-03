//
// Created by arseniy on 19.1.25.
//

#ifndef ITREECONNECTPATHGENERATOR_H
#define ITREECONNECTPATHGENERATOR_H
#include <components/solvers/treeSolvers/TreeNode.h>

#include "IPathGenerator.h"
#include "components/IComponent.h"

class ITreeConnectPathGenerator  : public IPathGenerator
{
public:
    virtual std::vector<Keyframe> generatePath(std::shared_ptr<TreeNode<Keyframe>> startTreeConnectionNode,
                                                std::shared_ptr<TreeNode<Keyframe>> goalTreeConnectionNode) = 0;
};



#endif //ITREECONNECTPATHGENERATOR_H
