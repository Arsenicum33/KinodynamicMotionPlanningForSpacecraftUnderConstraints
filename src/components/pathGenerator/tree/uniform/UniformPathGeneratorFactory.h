//
// Created by arseniy on 14.1.25.
//

#ifndef UNIFORMPATHGENERATORFACTORY_H
#define UNIFORMPATHGENERATORFACTORY_H
#include "components/IComponentFactory.h"
#include "components/pathGenerator/tree/ITreePathGenerator.h"


class UniformPathGeneratorFactory : public IComponentFactory<ITreePathGenerator<Pose>>
{
public:
    std::unique_ptr<ITreePathGenerator<Pose>> createComponent(const ComponentConfig &config, const ReaderContext &context) override;
};




#endif //UNIFORMPATHGENERATORFACTORY_H
