// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef RK4_KINODYNAMICSIMULATOR_H
#define RK4_KINODYNAMICSIMULATOR_H
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "components/dynamicsSimulators/RK4_DynamicsSimulator.h"


class RK4_KinodynamicSimulator  : public RK4_DynamicsSimulator<State>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context)
    {
        return std::make_unique<RK4_KinodynamicSimulator>();
    }

    void setDerivator(std::shared_ptr<IDerivator<State>> derivator) { this->derivator = derivator;}

    CapabilitySet getCapabilities() const override { return CapabilitySet{Capability::KinodynamicEnv}; };
};



#endif //RK4_KINODYNAMICSIMULATOR_H
