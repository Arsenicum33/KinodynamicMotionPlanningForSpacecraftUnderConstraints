//
// Created by arseniy on 14.1.25.
//

#ifndef UNIFORMPATHGENERATORFACTORY_H
#define UNIFORMPATHGENERATORFACTORY_H
#include "IPathGenerator.h"
#include "components/IComponentFactory.h"


class UniformPathGeneratorFactory : public IComponentFactory<IPathGenerator<Pose>>
{
public:
    std::shared_ptr<IPathGenerator<Pose>> createComponent(const ComponentConfig &config, const ReaderContext &context) override;
};




#endif //UNIFORMPATHGENERATORFACTORY_H
