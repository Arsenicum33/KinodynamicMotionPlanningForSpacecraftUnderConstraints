//
// Created by arseniy on 8.3.25.
//

#ifndef DEFAULTSTATICTERMINATIONCONDITIONFACTORY_H
#define DEFAULTSTATICTERMINATIONCONDITIONFACTORY_H
#include "components/IComponentFactory.h"
#include "components/terminationConditions/ITerminationCondition.h"


class DefaultTerminationConditionFactory: public IComponentFactory<ITerminationCondition<Pose,Pose>>
{
public:
    std::unique_ptr<ITerminationCondition<Pose,Pose>> createComponent(const ComponentConfig &config, const ReaderContext &context) override;
};

#endif //DEFAULTSTATICTERMINATIONCONDITIONFACTORY_H
