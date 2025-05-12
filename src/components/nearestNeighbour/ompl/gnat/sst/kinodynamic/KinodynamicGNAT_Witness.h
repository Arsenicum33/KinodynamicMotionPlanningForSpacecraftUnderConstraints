//
// Created by arseniy on 9.5.25.
//

#ifndef KINODYNAMICGNAT_WITNESS_H
#define KINODYNAMICGNAT_WITNESS_H
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "components/nearestNeighbour/ompl/gnat/sst/AGNAT_Witness.h"


class KinodynamicGNAT_Witness : public AGNAT_Witness<State>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context)
    {
        return std::make_unique<KinodynamicGNAT_Witness>();
    };
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::KinodynamicEnv}; }
    void build() override;
protected:
    std::shared_ptr<Witness<State>> searchedTypeToStoredType(const State &state) const override;


};



#endif //KINODYNAMICGNAT_WITNESS_H
