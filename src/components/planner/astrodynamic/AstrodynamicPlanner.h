//
// Created by arseniy on 30.4.25.
//

#ifndef ASTRODYNAMICPLANNER_H
#define ASTRODYNAMICPLANNER_H
#include "components/planner/IPlanner.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"


class AstrodynamicPlanner : public IPlanner<SpaceshipState>
{
public:
    AstrodynamicPlanner(double timeResolution) :
        IPlanner<SpaceshipState>(timeResolution) {}
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet{Capability::AstrodynamicEnv}; };
};



#endif //ASTRODYNAMICPLANNER_H
