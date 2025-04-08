//
// Created by arseniy on 8.4.25.
//

#ifndef QUATERNIONROTATIONEXPORTER_H
#define QUATERNIONROTATIONEXPORTER_H
#include <components/exporters/ATypedExporter.h>
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "DefaultKinodynamicExporter.h"


class QuaternionRotationExporter : public DefaultKinodynamicExporter
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    QuaternionRotationExporter(const std::string& filename, int fps) : DefaultKinodynamicExporter(filename,fps) {};

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::KinodynamicEnv, Capability::AstrodynamicEnv}; }

    Json::Value exportPositionTyped(const State &position, int frame) const override;
};



#endif //QUATERNIONROTATIONEXPORTER_H
