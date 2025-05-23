// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef DEFAULTDYNAMICEXPORTER_H
#define DEFAULTDYNAMICEXPORTER_H

#include "components/exporters/ATypedExporter.h"
#include "components/interpolators/dynamic/DynamicInterpolator.h"


class DefaultDynamicExporter : public ATypedExporter<Keyframe>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    DefaultDynamicExporter(const std::string& filename, int fps) : ATypedExporter(filename), fps(fps) {};

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::DynamicEnv, Capability::MovingTarget}; }


    Json::Value exportPositionTyped(const Keyframe &position, int frame) const override;

    void exportPositionsTyped(std::vector<Keyframe> positions) const override;

private:
    int fps;
};


#endif //DEFAULTDYNAMICEXPORTER_H
