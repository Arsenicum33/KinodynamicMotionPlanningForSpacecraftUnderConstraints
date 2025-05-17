//
// Created by arseniy on 3.5.25.
//

#ifndef ASTRODYNAMICGNATSEARCH_H
#define ASTRODYNAMICGNATSEARCH_H
#include "components/nearestNeighbour/ompl/gnat/AGNATsearch.h"
#include "components/nearestNeighbour/ompl/gnat/sst/AGNAT_SST.h"
#include "components/solvers/SST/SSTnode.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"


class AstrodynamicGNAT_SST : public AGNAT_SST<SpaceshipState>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context)
    {
        return std::make_unique<AstrodynamicGNAT_SST>();
    };
    CapabilitySet getCapabilities() const override { return CapabilitySet{Capability::AstrodynamicEnv};}

    void build() override;

protected:
    std::shared_ptr<SSTnode<SpaceshipState>> searchedTypeToStoredType(const SpaceshipState &state) const override;

};



#endif //ASTRODYNAMICGNATSEARCH_H
