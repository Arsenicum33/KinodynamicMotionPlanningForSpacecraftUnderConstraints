// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef DEFAULTEXPORTER_H
#define DEFAULTEXPORTER_H
#include <components/exporters/ATypedExporter.h>

class DefaultExporter : public ATypedExporter<Pose>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    DefaultExporter(const std::string& filename) : ATypedExporter(filename) {};

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv}; }

    Json::Value exportPositionTyped(const Pose &position, int frame) const override;
};



#endif //DEFAULTEXPORTER_H
