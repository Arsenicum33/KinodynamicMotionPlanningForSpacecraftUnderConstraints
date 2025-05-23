// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


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
