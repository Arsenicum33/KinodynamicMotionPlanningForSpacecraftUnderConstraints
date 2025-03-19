//
// Created by arseniy on 17.1.25.
//

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

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

    void exportPositionsTyped(std::vector<Keyframe> positions) const override;

private:
    int fps;
    std::shared_ptr<IDynamicInterpolator> interpolator;
};


#endif //DEFAULTDYNAMICEXPORTER_H
