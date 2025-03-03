//
// Created by arseniy on 17.1.25.
//

#ifndef DEFAULTDYNAMICPATHGENERATORFACTORY_H
#define DEFAULTDYNAMICPATHGENERATORFACTORY_H
#include "DefaultDynamicPathGenerator.h"
#include "IPathGenerator.h"
#include "ITreePathGenerator.h"
#include "components/IComponentFactory.h"


class DefaultDynamicPathGeneratorFactory : public IComponentFactory<ITreePathGenerator<Keyframe>>
{
public:
    std::unique_ptr<ITreePathGenerator<Keyframe>> createComponent(const ComponentConfig &config, const ReaderContext &context) override
    {
        return std::make_unique<DefaultDynamicPathGenerator>();
    };
};


#endif //DEFAULTDYNAMICPATHGENERATORFACTORY_H
