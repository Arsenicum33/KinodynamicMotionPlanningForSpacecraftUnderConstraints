//
// Created by arseniy on 9.5.25.
//

#ifndef KINODYNAMICTIMESSTCOSTFUNCTION_H
#define KINODYNAMICTIMESSTCOSTFUNCTION_H
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "components/costFunctions/ISSTcostFunction.h"


class KinodynamicTimeSSTcostFunction : public ISSTcostFunction<State>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context)
    {
        return std::make_unique<KinodynamicTimeSSTcostFunction>();
    }
    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::KinodynamicEnv }; };

    double getCost(std::shared_ptr<SSTnode<State>> parent, const State &currentState) override;
};



#endif //KINODYNAMICTIMESSTCOSTFUNCTION_H
