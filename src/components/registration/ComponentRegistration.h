//
// Created by arseniy on 12.1.25.
//
#pragma once

#include <components/exporters/defaultExporter/DefaultExporter.h>
#include <components/nearestNeighbour/mpnn/AMPNNsearch.h>
#include <components/pathGenerator/tree/uniform/UniformPathGenerator.h>

#include "ComponentRegistry.h"
#include "components/collisionHandlers/dynamic/DynamicCollisionHandler.h"
#include "components/collisionHandlers/kinodynamic/StateCollisionHandlerAdapter.h"
#include "components/collisionHandlers/static/StaticCollisionHandler.h"
#include "components/constraintsEnforcer/ConstraintsEnforcer.h"
#include "components/distanceMeasurement/defaultSpatial/DefaultSpatialDistanceMetric.h"
#include "components/distanceMeasurement/temporalTotal/TemporalTransRotMetric.h"
#include "components/dynamicsSimulators/DynamicsSimulator.h"
#include "components/dynamicsSimulators/burst/BurstDynamicsSimulatorAdapter.h"
#include "components/exporters/dynamicExporter/DefaultDynamicExporter.h"
#include "components/exporters/kinodynamicExporter/DefaultKinodynamicExporter.h"
#include "components/exporters/kinodynamicExporter/QuaternionRotationExporter.h"
#include "components/interpolators/dynamic/DynamicInterpolator.h"
#include "components/interpolators/kinodynamic/KinodynamicLinearInterpolator.h"
#include "components/interpolators/static/StaticInterpolator.h"
#include "components/nearestNeighbour/mpnn/dynamic/DynamicMPNNsearch.h"
#include "components/nearestNeighbour/mpnn/static/StaticMPNNsearch.h"
#include "components/nearestNeighbour/temporalMPNN/TemporalMPNNsearch.h"
#include "components/pathGenerator/tree/dynamic/DefaultDynamicPathGenerator.h"
#include "components/pathGenerator/tree/dynamic/kinodynamic/KinodynamicPathGenerator.h"
#include "components/propulsionSystem/burst/BurstPropulsionSystem.h"
#include "components/propulsionSystem/simpleContinuous/SimpleContinuousPropulsionSystem.h"
#include "components/sampling/controlInputSampling/burst/BurstControlInputSampler.h"
#include "components/sampling/controlInputSampling/default/ControlInputSampler.h"
#include "components/sampling/controlInputSampling/rotationStabilizing/StabilizingControlInputSampler.h"
#include "components/sampling/positionSampling/dynamic/biased/DynamicBiasedRandomSampler.h"
#include "components/sampling/positionSampling/dynamic/default/DynamicRandomSampler.h"
#include "components/sampling/positionSampling/dynamic/movingTarget/MovingTargetBiasedSampler.h"
#include "components/sampling/positionSampling/static/biased/StaticBiasedRandomSampler.h"
#include "components/sampling/positionSampling/static/default/StaticRandomSampler.h"
#include "components/solvers/dynamic/kinodynamic/KinodynamicRRTsolver.h"
#include "components/terminationConditions/dynamic/DynamicTerminationCondition.h"
#include "components/terminationConditions/movingTarget/MovingTargetTerminationCondition.h"
#include "components/terminationConditions/static/StaticTerminationCondition.h"
#include "components/solvers/static/RRT/RRTsolver.h"
#include "components/solvers/dynamic/movingTarget/MT_TARRTsolver.h"
#include "components/terminationConditions/kinodynamic/KinodynamicTerminationCondition.h"
#include "components/solvers/dynamic/TARRT/TAGeometricRRTsolver.h"
#include "components/solvers/utils/statePropagators/StatePropagator.h"
#include "components/solvers/utils/statePropagators/State_BurstControlInput_StatePropagator.h"
#include "components/solvers/utils/statePropagators/State_ControlInput_StatePropagator.h"

REGISTER_COMPONENT(StaticCollisionHandler);
REGISTER_COMPONENT(RRTsolver);
REGISTER_COMPONENT(TAGeometricRRTsolver);
REGISTER_COMPONENT(StaticMPNNsearch);
REGISTER_COMPONENT(DynamicMPNNsearch);
REGISTER_COMPONENT(DefaultSpatialDistanceMetric);
REGISTER_COMPONENT(UniformPathGenerator);
REGISTER_COMPONENT(StaticRandomSampler);
REGISTER_COMPONENT(DynamicRandomSampler);
REGISTER_COMPONENT(DefaultExporter);
REGISTER_COMPONENT(DynamicCollisionHandler);
REGISTER_COMPONENT(DefaultDynamicPathGenerator);
REGISTER_COMPONENT(DefaultDynamicExporter);
REGISTER_COMPONENT(StaticTerminationCondition);
REGISTER_COMPONENT(MovingTargetTerminationCondition);
REGISTER_COMPONENT(StaticBiasedRandomSampler);
REGISTER_COMPONENT(DynamicBiasedRandomSampler);
REGISTER_COMPONENT(MovingTargetBiasedSampler);
REGISTER_COMPONENT(TemporalMPNNsearch);
REGISTER_COMPONENT(MT_TARRTsolver);
REGISTER_COMPONENT(TemporalTransRotMetric);
REGISTER_COMPONENT(StaticInterpolator);
REGISTER_COMPONENT(DynamicInterpolator);
REGISTER_COMPONENT(DynamicTerminationCondition);
REGISTER_COMPONENT(StateCollisionHandlerAdapter);
REGISTER_COMPONENT(DynamicsSimulator);
REGISTER_COMPONENT(DefaultKinodynamicExporter);
REGISTER_COMPONENT(KinodynamicLinearInterpolator);
REGISTER_COMPONENT(KinodynamicPathGenerator);
REGISTER_COMPONENT(ControlInputSampler);
REGISTER_COMPONENT(KinodynamicRRTsolver);
REGISTER_COMPONENT(KinodynamicTerminationCondition);
REGISTER_COMPONENT(StabilizingControlInputSampler);
REGISTER_COMPONENT(ConstraintsEnforcer);
REGISTER_COMPONENT(State_ControlInput_StatePropagator);
REGISTER_COMPONENT(State_BurstControlInput_StatePropagator);
REGISTER_COMPONENT(BurstPropulsionSystem);
REGISTER_COMPONENT(SimpleContinuousPropulsionSystem);
REGISTER_COMPONENT(BurstDynamicsSimulatorAdapter);
REGISTER_COMPONENT(BurstControlInputSampler);
REGISTER_COMPONENT(QuaternionRotationExporter);