//
// Created by arseniy on 12.1.25.
//
#pragma once

#include <components/exporters/defaultExporter/DefaultExporter.h>
#include <components/nearestNeighbour/mpnn/AMPNNsearch.h>
#include <components/pathGenerator/tree/uniform/UniformPathGenerator.h>

#include "ComponentRegistry.h"
#include "components/agentModel/kinodynamicAgentModel/KinodynamicAgentModel.h"
#include "components/agentModel/spacecraftModel/SpacecraftModel.h"
#include "components/collisionHandlers/astrodynamic/AstrodynamicCollisionHandler.h"
#include "components/collisionHandlers/dynamic/DynamicCollisionHandler.h"
#include "components/collisionHandlers/kinodynamic/StateCollisionHandlerAdapter.h"
#include "components/collisionHandlers/static/StaticCollisionHandler.h"
#include "components/constraintsEnforcer/astrodynamic/AstrodynamicConstraintsEnforcer.h"
#include "components/constraintsEnforcer/kinodynamic/KinodynamicConstraintsEnforcer.h"
#include "components/costFunctions/astrodynamic/fuel/AstrodynamicFuelSSTcostFunction.h"
#include "components/costFunctions/astrodynamic/time/AstrodynamicTimeSSTcostFunction.h"
#include "components/costFunctions/kinodynamic/time/KinodynamicTimeSSTcostFunction.h"
#include "components/derivator/astrodynamic/AstrodynamicDerivator.h"
#include "components/distanceMeasurement/defaultSpatial/DefaultSpatialDistanceMetric.h"
#include "components/distanceMeasurement/temporalTotal/TemporalTransRotMetric.h"
#include "components/dynamicsSimulators/astrodynamic/EulerAstrodynamicSimulator.h"
#include "components/dynamicsSimulators/astrodynamic/RK4_AstrodynamicSimulator.h"
#include "components/dynamicsSimulators/kinodynamic/RK4_KinodynamicSimulator.h"
#include "components/exporters/astrodynamicExporter/AstrodynamicExporter.h"
#include "components/exporters/dynamicExporter/DefaultDynamicExporter.h"
#include "components/exporters/kinodynamicExporter/KinodynamicExporter.h"
#include "components/fuelSystem/FuelSystem.h"
#include "components/interpolators/astrodynamic/AstrodynamicInterpolator.h"
#include "components/interpolators/dynamic/DynamicInterpolator.h"
#include "components/interpolators/kinodynamic/KinodynamicLinearInterpolator.h"
#include "components/interpolators/static/StaticInterpolator.h"
#include "components/nearestNeighbour/mpnn/dynamic/DynamicMPNNsearch.h"
#include "components/nearestNeighbour/mpnn/static/StaticMPNNsearch.h"
#include "components/nearestNeighbour/ompl/gnat/sst/astrodynamic/AstrodynamicGNAT_SST.h"
#include "components/nearestNeighbour/ompl/gnat/sst/astrodynamic/AstrodynamicGNAT_Witness.h"
#include "components/nearestNeighbour/ompl/gnat/sst/kinodynamic/KinodynamicGNAT_SST.h"
#include "components/nearestNeighbour/ompl/gnat/sst/kinodynamic/KinodynamicGNAT_Witness.h"
#include "components/nearestNeighbour/temporalMPNN/TemporalMPNNsearch.h"
#include "components/pathGenerator/sst/astrodynamic/AstrodynamicSSTpathGenerator.h"
#include "components/pathGenerator/sst/kinodynamic/KinodynamicSSTpathGenerator.h"
#include "components/pathGenerator/tree/dynamic/DefaultDynamicPathGenerator.h"
#include "components/pathGenerator/tree/dynamic/astrodynamic/AstrodynamicPathGenerator.h"
#include "components/pathGenerator/tree/dynamic/kinodynamic/KinodynamicPathGenerator.h"
#include "components/physics/externalForceComputer/AstrodynamicExternalForcesComputer.h"
#include "components/physics/forceToAccelerationConverter/AstrodynamicForceToAccelerationConverter.h"
#include "components/physics/forceToAccelerationConverter/KinodynamicForceToAccelerationConverter.h"
#include "components/physics/interactions/AstrodynamicGravityInteraction.h"
#include "components/physics/internalForcesComputer/AstrodynamicInternalForcesComputer.h"
#include "components/physics/internalForcesComputer/KinodynamicInternalForcesComputer.h"
#include "components/physics/physicsSimulator/AstrodynamicPhysicsSimulator.h"
#include "components/physics/physicsSimulator/KinodynamicPhysicsSimulator.h"
#include "components/planner/astrodynamic/AstrodynamicPlanner.h"
#include "components/planner/kinodynamic/KinodynamicPlanner.h"
#include "components/propulsionSystem/burst/BurstPropulsionSystem.h"
#include "components/sampling/controlInputSampling/burst/BurstControlInputSampler.h"
#include "components/sampling/controlInputSampling/burst/astrodynamic/AstrodynamicBurstSampler.h"
#include "components/sampling/controlInputSampling/default/ControlInputSampler.h"
#include "components/sampling/controlInputSampling/rotationStabilizing/StabilizingControlInputSampler.h"
#include "components/sampling/positionSampling/dynamic/astrodynamic/AstrodynamicBiasedRandomSampler.h"
#include "components/sampling/positionSampling/dynamic/biased/DynamicBiasedRandomSampler.h"
#include "components/sampling/positionSampling/dynamic/default/DynamicRandomSampler.h"
#include "components/sampling/positionSampling/dynamic/movingTarget/MovingTargetBiasedSampler.h"
#include "components/sampling/positionSampling/static/biased/StaticBiasedRandomSampler.h"
#include "components/sampling/positionSampling/static/default/StaticRandomSampler.h"
#include "components/solvers/RRT/dynamic/astrodynamic/AstrodynamicRRTsolver.h"
#include "components/solvers/RRT/dynamic/kinodynamic/KinodynamicRRTsolver.h"
#include "components/terminationConditions/dynamic/DynamicTerminationCondition.h"
#include "components/terminationConditions/movingTarget/MovingTargetTerminationCondition.h"
#include "components/terminationConditions/static/StaticTerminationCondition.h"
#include "components/solvers/RRT/static/RRT/RRTsolver.h"
#include "components/solvers/RRT/dynamic/movingTarget/MT_TARRTsolver.h"
#include "components/terminationConditions/kinodynamic/KinodynamicTerminationCondition.h"
#include "components/solvers/RRT/dynamic/TARRT/TAGeometricRRTsolver.h"
#include "components/solvers/utils/statePropagators/StatePropagator.h"
#include "components/solvers/utils/statePropagators/KinodynamicStatePropagator.h"
#include "components/terminationConditions/astrodynamic/AstrodynamicTerminationCondition.h"
#include "components/sampling/controlInputSampling/burst/astrodynamic/AstrodynamicBurstSampler.h"
#include "components/sampling/controlInputSampling/burst/kinodynamic/KinodynamicBurstSampler.h"
#include "components/sampling/positionSampling/dynamic/astrodynamic/BiasedSphericalBoundariesSampler/BiasedSphericalBoundariesSampler.h"
#include "components/sampling/positionSampling/dynamic/astrodynamic/BiasedSphericalBoundariesSampler/AstrodynamicBiasedSphericalBoundariesSampler.h"
#include "components/sampling/positionSampling/dynamic/kinodynamic/KinodynamicBiasedSampler.h"
#include "components/solvers/SST/astrodynamic/AstrodynamicSSTsolver.h"
#include "components/solvers/SST/kinodynamic/KinodynamicSSTsolver.h"
#include "components/solvers/utils/statePropagators/AstrodynamicStatePropagator.h"

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
REGISTER_COMPONENT(KinodynamicLinearInterpolator);
REGISTER_COMPONENT(KinodynamicPathGenerator);
REGISTER_COMPONENT(ControlInputSampler);
REGISTER_COMPONENT(KinodynamicRRTsolver);
REGISTER_COMPONENT(KinodynamicTerminationCondition);
REGISTER_COMPONENT(StabilizingControlInputSampler);
REGISTER_COMPONENT(KinodynamicConstraintsEnforcer);
REGISTER_COMPONENT(BurstPropulsionSystem);
REGISTER_COMPONENT(AstrodynamicCollisionHandler);
REGISTER_COMPONENT(AstrodynamicRRTsolver);
REGISTER_COMPONENT(AstrodynamicPathGenerator);
REGISTER_COMPONENT(AstrodynamicBiasedRandomSampler);
REGISTER_COMPONENT(AstrodynamicExporter);
REGISTER_COMPONENT(AstrodynamicTerminationCondition);
REGISTER_COMPONENT(AstrodynamicInterpolator);
REGISTER_COMPONENT(AstrodynamicBurstSampler);
REGISTER_COMPONENT(AstrodynamicConstraintsEnforcer);
REGISTER_COMPONENT(AstrodynamicStatePropagator);
REGISTER_COMPONENT(AstrodynamicPhysicsSimulator);
REGISTER_COMPONENT(AstrodynamicInternalForcesComputer);
REGISTER_COMPONENT(AstrodynamicExternalForcesComputer);
REGISTER_COMPONENT(AstrodynamicForceToAccelerationConverter);
REGISTER_COMPONENT(AstrodynamicGravityInteraction);
REGISTER_COMPONENT(FuelSystem);
REGISTER_COMPONENT(BiasedSphericalBoundariesSampler);

REGISTER_COMPONENT(AstrodynamicPlanner);
REGISTER_COMPONENT(KinodynamicPlanner);
REGISTER_COMPONENT(AstrodynamicDerivator);
REGISTER_COMPONENT(RK4_AstrodynamicSimulator);
REGISTER_COMPONENT(EulerAstrodynamicSimulator);

REGISTER_COMPONENT(AstrodynamicSSTsolver);
REGISTER_COMPONENT(AstrodynamicSSTpathGenerator);
REGISTER_COMPONENT(AstrodynamicGNAT_SST);
REGISTER_COMPONENT(AstrodynamicGNAT_Witness);
REGISTER_COMPONENT(AstrodynamicTimeSSTcostFunction);
REGISTER_COMPONENT(AstrodynamicFuelSSTcostFunction);
REGISTER_COMPONENT(AstrodynamicBiasedSphericalBoundariesSampler);
REGISTER_COMPONENT(KinodynamicPhysicsSimulator);
REGISTER_COMPONENT(KinodynamicAgentModel);
REGISTER_COMPONENT(SpacecraftModel);
REGISTER_COMPONENT(KinodynamicForceToAccelerationConverter);
REGISTER_COMPONENT(KinodynamicExporter);
REGISTER_COMPONENT(KinodynamicBurstSampler);
REGISTER_COMPONENT(RK4_KinodynamicSimulator);
REGISTER_COMPONENT(KinodynamicInternalForcesComputer);
REGISTER_COMPONENT(KinodynamicDerivator);
REGISTER_COMPONENT(KinodynamicStatePropagator);
REGISTER_COMPONENT(KinodynamicSSTsolver);
REGISTER_COMPONENT(KinodynamicGNAT_SST);
REGISTER_COMPONENT(KinodynamicGNAT_Witness);
REGISTER_COMPONENT(KinodynamicBiasedSampler);
REGISTER_COMPONENT(KinodynamicTimeSSTcostFunction);
REGISTER_COMPONENT(KinodynamicSSTpathGenerator);