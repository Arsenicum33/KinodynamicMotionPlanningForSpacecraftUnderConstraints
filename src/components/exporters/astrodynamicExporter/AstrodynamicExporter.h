// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef ASTRODYNAMICEXPORTER_H
#define ASTRODYNAMICEXPORTER_H
#include <components/exporters/ATypedExporter.h>

#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"

#define ANGULAR_VELOCITY_SCALING_FACTOR 1e4

class AstrodynamicExporter : public ATypedExporter<SpaceshipState>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    AstrodynamicExporter(const std::string& filename, int fps) : ATypedExporter(filename), fps(fps) {};

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv}; }

    void exportPositionsTyped(std::vector<SpaceshipState> positions) const override;

    Json::Value exportPositionTyped(const SpaceshipState &position, int frame) const override;

private:
    void scalePositions(std::vector<SpaceshipState> &positions) const;
    int fps;
};



#endif //ASTRODYNAMICEXPORTER_H
