//
// Created by arseniy on 5.5.25.
//

#ifndef ASTRODYNAMICSSTPATHGENERATOR_H
#define ASTRODYNAMICSSTPATHGENERATOR_H
#include "components/pathGenerator/sst/ISSTpathGenerator.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"


class AstrodynamicSSTpathGenerator : public ISSTpathGenerator<SpaceshipState>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context)
    {
        return std::make_unique<AstrodynamicSSTpathGenerator>();
    }
    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::AstrodynamicEnv }; };

};



#endif //ASTRODYNAMICSSTPATHGENERATOR_H
