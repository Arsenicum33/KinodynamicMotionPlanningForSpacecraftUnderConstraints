// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


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
