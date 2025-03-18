//
// Created by arseniy on 23.10.24.
//

#ifndef DEFAULTEXPORTER_H
#define DEFAULTEXPORTER_H
#include <components/exporters/ATypedExporter.h>

class DefaultExporter : public ATypedExporter<Pose>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    DefaultExporter(const std::string& filename) : ATypedExporter(filename) {};

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv}; }

    void exportPositionsTyped(std::vector<Pose> positions) const override;
};



#endif //DEFAULTEXPORTER_H
