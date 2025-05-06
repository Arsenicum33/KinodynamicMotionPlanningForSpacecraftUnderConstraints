//
// Created by arseniy on 5.5.25.
//

#ifndef ASTRODYNAMICGNAT_WITNESS_H
#define ASTRODYNAMICGNAT_WITNESS_H
#include "components/nearestNeighbour/ompl/gnat/sst/AGNAT_Witness.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"


class AstrodynamicGNAT_Witness : public AGNAT_Witness<SpaceshipState>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context)
    {
        return std::make_unique<AstrodynamicGNAT_Witness>();
    };
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv}; }
    void build() override;
protected:
    std::shared_ptr<Witness<SpaceshipState>> searchedTypeToStoredType(const SpaceshipState &state) const override;


};



#endif //ASTRODYNAMICGNAT_WITNESS_H
