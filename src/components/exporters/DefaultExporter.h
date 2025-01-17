//
// Created by arseniy on 23.10.24.
//

#ifndef DEFAULTEXPORTER_H
#define DEFAULTEXPORTER_H
#include "AbstractExporter.h"


class DefaultExporter : public AbstractExporter<Pose>
{
public:
    DefaultExporter(const std::string& filename) : AbstractExporter(filename) {};
    std::vector<Pose> exportPoses(std::vector<Pose>& poses) override;
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv}; }

};



#endif //DEFAULTEXPORTER_H
