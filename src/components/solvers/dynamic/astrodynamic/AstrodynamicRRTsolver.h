//
// Created by arseniy on 11.4.25.
//

#ifndef ASTRODYNAMICRRTSOLVER_H
#define ASTRODYNAMICRRTSOLVER_H
#include <components/solvers/dynamic/kinodynamic/AKinodynamicRRTsolver.h>

#include "dto/poses/astrodynamic/celestialBody/CelestialBody.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"

class AstrodynamicRRTsolver : public AKinodynamicRRTsolver<SpaceshipState, CelestialBody, Keyframe>
{
public:
    AstrodynamicRRTsolver(int maxIterations, int outputPeriod, int controlInputSamples)
     : AKinodynamicRRTsolver<SpaceshipState, CelestialBody, Keyframe>(
         maxIterations, outputPeriod, controlInputSamples) {}

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::KinodynamicEnv }; }

};
#endif //ASTRODYNAMICRRTSOLVER_H
