//
// Created by arseniy on 19.1.25.
//

#ifndef TREECONNECTPATHGENERATORFACTORY_H
#define TREECONNECTPATHGENERATORFACTORY_H
#include "TreeConnectPathGenerator.h"
#include "components/IComponentFactory.h"


class TreeConnectPathGeneratorFactory : public IComponentFactory<TreeConnectPathGenerator>
{
public:
    std::unique_ptr<TreeConnectPathGenerator> createComponent(const ComponentConfig &config, const ReaderContext &context) override
    {
        return std::make_unique<TreeConnectPathGenerator>();
    };
};


#endif //TREECONNECTPATHGENERATORFACTORY_H
