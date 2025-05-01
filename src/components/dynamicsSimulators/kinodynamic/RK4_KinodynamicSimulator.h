//
// Created by arseniy on 30.4.25.
//

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

    CapabilitySet getCapabilities() const override { return CapabilitySet{Capability::KinodynamicEnv}; };
};



#endif //RK4_KINODYNAMICSIMULATOR_H
