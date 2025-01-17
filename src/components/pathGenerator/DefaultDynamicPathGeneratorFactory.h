//
// Created by arseniy on 17.1.25.
//

#ifndef DEFAULTDYNAMICPATHGENERATORFACTORY_H
#define DEFAULTDYNAMICPATHGENERATORFACTORY_H
#include "DefaultDynamicPathGenerator.h"
#include "IPathGenerator.h"
#include "components/IComponentFactory.h"


class DefaultDynamicPathGeneratorFactory : public IComponentFactory<IPathGenerator<Keyframe>>
{
public:
    std::shared_ptr<IPathGenerator<Keyframe>> createComponent(const ComponentConfig &config, const ReaderContext &context) override
    {
        return std::make_shared<DefaultDynamicPathGenerator>();
    };
};


#endif //DEFAULTDYNAMICPATHGENERATORFACTORY_H
