//
// Created by arseniy on 17.1.25.
//

#ifndef DEFAULTDYNAMICEXPORTER_H
#define DEFAULTDYNAMICEXPORTER_H
#include "AbstractExporter.h"


class DefaultDynamicExporter : public AbstractExporter<Keyframe>
{
public:
    DefaultDynamicExporter(const std::string& filename, int fps) : AbstractExporter(filename), fps(fps) {};
    std::vector<Keyframe> exportPoses(std::vector<Keyframe>& keyframes) override;
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv, Capability::DynamicEnv}; }
private:
    int fps;
};


#endif //DEFAULTDYNAMICEXPORTER_H
