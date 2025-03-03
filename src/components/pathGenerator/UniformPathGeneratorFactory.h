//
// Created by arseniy on 14.1.25.
//

#ifndef UNIFORMPATHGENERATORFACTORY_H
#define UNIFORMPATHGENERATORFACTORY_H
#include "IPathGenerator.h"
#include "ITreePathGenerator.h"
#include "components/IComponentFactory.h"


class UniformPathGeneratorFactory : public IComponentFactory<ITreePathGenerator<Pose>>
{
public:
    std::unique_ptr<ITreePathGenerator<Pose>> createComponent(const ComponentConfig &config, const ReaderContext &context) override;
};




#endif //UNIFORMPATHGENERATORFACTORY_H
