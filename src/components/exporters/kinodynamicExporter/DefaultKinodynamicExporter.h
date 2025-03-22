//
// Created by arseniy on 22.3.25.
//

#ifndef DEFAULTKINODYNAMICEXPORTER_H
#define DEFAULTKINODYNAMICEXPORTER_H
#include "components/exporters/ATypedExporter.h"
#include "dto/poses/dynamic/kinodynamic/state/State.h"


class DefaultKinodynamicExporter : public ATypedExporter<State>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    DefaultKinodynamicExporter(const std::string& filename, int fps) : ATypedExporter(filename), fps(fps) {};

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::DynamicEnv, Capability::MovingTarget}; }

    void exportPositionsTyped(std::vector<State> positions) const override;

    Json::Value exportPositionTyped(const State &position, int frame) const override;

private:
    int fps;
};



#endif //DEFAULTKINODYNAMICEXPORTER_H
