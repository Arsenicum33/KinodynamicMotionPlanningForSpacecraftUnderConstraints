//
// Created by arseniy on 8.5.25.
//

#ifndef KINODYNAMICEXPORTER_H
#define KINODYNAMICEXPORTER_H
#include <components/exporters/ATypedExporter.h>
#include <dto/poses/dynamic/kinodynamic/state/State.h>


class KinodynamicExporter : public ATypedExporter<State>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    KinodynamicExporter(const std::string& filename, int fps) : ATypedExporter(filename), fps(fps) {};

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::KinodynamicEnv}; }

    void exportPositionsTyped(std::vector<State> positions) const override;

    Json::Value exportPositionTyped(const State &position, int frame) const override;

private:
    int fps;
};


#endif //KINODYNAMICEXPORTER_H
