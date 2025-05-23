cmake_minimum_required(VERSION 3.29)
project(PathPlanning3D)


# Set build type to Debug to disable optimizations
#set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)

# Ensure Debug build has no optimizations and full debug info
#set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ggdb" CACHE STRING "Flags used by the C++ compiler during Debug builds." FORCE)

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find external packages
find_package(Eigen3 REQUIRED)
find_package(jsoncpp REQUIRED)

# Paths to static libraries
set(RAPID_LIB_DIR ${CMAKE_SOURCE_DIR}/../libraries/rapid/build)
set(MPNN_LIB_DIR ${CMAKE_SOURCE_DIR}/../libraries/mpnn/build)
set(FBX_LIB_DIR ${CMAKE_SOURCE_DIR}/../libraries/fbx_sdk/lib/release)
set(SPDLOG_LIB_DIR ${CMAKE_SOURCE_DIR}/../libraries/spdlog/build)
set(GTEST_LIB_DIR ${CMAKE_SOURCE_DIR}/../libraries/gtest/build/lib)

set(RAPID_STATIC_LIB ${RAPID_LIB_DIR}/libRAPID.a)
set(MPNN_STATIC_LIB ${MPNN_LIB_DIR}/libDNN.a)
set(SPDLOG_STATIC_LIB ${SPDLOG_LIB_DIR}/libspdlog.a)
set(GTEST_STATIC_LIB ${GTEST_LIB_DIR}/libgtest.a)
set(GTEST_MAIN_STATIC_LIB ${GTEST_LIB_DIR}/libgtest_main.a)

add_definitions(-DSPDLOG_COMPILED_LIB)
add_definitions(-DBOOST_ALL_NO_LIB -DBOOST_SYSTEM_NO_DEPRECATED)
# Define source files (excluding main.cpp and headers)
set(SOURCE_FILES
        src/dto/poses/static/poseMath/PoseMath.cpp
        src/dto/poses/static/pose/Pose.cpp
        src/input/meshParsers/rapidObjMeshParser/RapidObjMeshParser.cpp
        src/dto/configurationSpaceBoundaries/ConfigurationSpaceBoundaries.cpp
        src/components/exporters/defaultExporter/DefaultExporter.cpp
        src/input/inputParser/InputParser.cpp
        src/components/distanceMeasurement/euclidian/EuclidianDistanceMetric.cpp
        src/components/distanceMeasurement/defaultSpatial/DefaultSpatialDistanceMetric.cpp
        src/components/pathGenerator/tree/uniform/UniformPathGenerator.cpp
        src/dto/poses/dynamic/keyframe/Keyframe.cpp
        src/input/componentsParser/ComponentsParser.cpp
        src/core/Program.cpp
        src/core/creator/ComponentManager.cpp
        src/core/executor/Executor.cpp
        src/core/exporter/HighLevelExporter.cpp
        src/core/reader/Reader.cpp
        src/core/validator/Validator.cpp
        src/core/reader/readerFactory/DefaultReaderFactory.cpp
        src/components/exporters/dynamicExporter/DefaultDynamicExporter.cpp
        src/components/capabilities/manager/CapabilityManager.cpp
        src/components/terminationConditions/static/StaticTerminationCondition.cpp
        src/components/terminationConditions/movingTarget/MovingTargetTerminationCondition.cpp
        src/components/distanceMeasurement/temporalTotal/TemporalTransRotMetric.cpp
        src/components/interpolators/dynamic/DynamicInterpolator.cpp
        src/components/interpolators/static/StaticInterpolator.cpp
        src/components/collisionHandlers/static/StaticCollisionHandler.cpp
        src/components/collisionHandlers/dynamic/DynamicCollisionHandler.cpp
        src/components/sampling/positionSampling/dynamic/default/DynamicRandomSampler.cpp
        src/components/sampling/positionSampling/dynamic/biased/DynamicBiasedRandomSampler.cpp
        src/components/sampling/positionSampling/static/default/StaticRandomSampler.cpp
        src/components/sampling/positionSampling/static/biased/StaticBiasedRandomSampler.cpp
        src/components/sampling/positionSampling/dynamic/movingTarget/MovingTargetBiasedSampler.cpp
        src/components/terminationConditions/dynamic/DynamicTerminationCondition.cpp
        src/components/solvers/RRT/dynamic/TARRT/TAGeometricRRTsolver.cpp
        src/components/solvers/RRT/dynamic/movingTarget/MT_TARRTsolver.cpp
        src/components/solvers/RRT/static/RRT/RRTsolver.cpp
        src/dto/poses/dynamic/kinodynamic/state/State.cpp
        src/dto/poses/dynamic/kinodynamic/controlInput/ControlInput.cpp
        src/components/solvers/RRT/dynamic/kinodynamic/KinodynamicRRTsolver.cpp
        src/components/sampling/controlInputSampling/default/ControlInputSampler.cpp
        src/components/interpolators/kinodynamic/KinodynamicLinearInterpolator.cpp
        src/components/terminationConditions/kinodynamic/KinodynamicTerminationCondition.cpp
        src/components/nearestNeighbour/ompl/gnat/AGNATsearch.cpp
        src/components/nearestNeighbour/ompl/gnat/AGNATsearch.h
        src/components/nearestNeighbour/ompl/OMPLnnSearch.h
        src/components/nearestNeighbour/INearestNeighborSearch.h
        src/components/nearestNeighbour/ompl/gnat/sst/astrodynamic/AstrodynamicGNAT_SST.cpp
        src/components/nearestNeighbour/ompl/gnat/sst/astrodynamic/AstrodynamicGNAT_SST.h
        src/components/solvers/ATypedSolver.h
        src/components/solvers/SST/ASSTsolver.h
        src/components/solvers/SST/Witness.h
        src/components/solvers/SST/SSTnode.h
        src/components/nearestNeighbour/ompl/gnat/sst/AGNAT_SST.h
        src/components/nearestNeighbour/ompl/gnat/sst/AGNAT_Witness.h
        src/components/costFunctions/ISSTcostFunction.h
        src/components/pathGenerator/sst/ISSTpathGenerator.h
        src/components/solvers/SST/astrodynamic/AstrodynamicSSTsolver.cpp
        src/components/solvers/SST/astrodynamic/AstrodynamicSSTsolver.h
        src/components/nearestNeighbour/ompl/gnat/sst/astrodynamic/AstrodynamicGNAT_Witness.cpp
        src/components/nearestNeighbour/ompl/gnat/sst/astrodynamic/AstrodynamicGNAT_Witness.h
        src/components/costFunctions/astrodynamic/time/AstrodynamicTimeSSTcostFunction.cpp
        src/components/costFunctions/astrodynamic/time/AstrodynamicTimeSSTcostFunction.h
        src/components/pathGenerator/sst/astrodynamic/AstrodynamicSSTpathGenerator.cpp
        src/components/pathGenerator/sst/astrodynamic/AstrodynamicSSTpathGenerator.h
        src/components/sampling/positionSampling/dynamic/astrodynamic/BiasedSphericalBoundariesSampler/AstrodynamicBiasedSphericalBoundariesSampler.cpp
        src/components/sampling/positionSampling/dynamic/astrodynamic/BiasedSphericalBoundariesSampler/AstrodynamicBiasedSphericalBoundariesSampler.h
        src/components/physics/physicsSimulator/KinodynamicPhysicsSimulator.h
        src/components/physics/internalForcesComputer/KinodynamicInternalForcesComputer.h
        src/components/physics/forceToAccelerationConverter/KinodynamicForceToAccelerationConverter.h
        src/components/agentModel/spacecraftModel/SpacecraftModel.cpp
        src/components/agentModel/spacecraftModel/SpacecraftModel.h
        src/components/agentModel/kinodynamicAgentModel/KinodynamicAgentModel.cpp
        src/components/agentModel/kinodynamicAgentModel/KinodynamicAgentModel.h
        src/components/agentModel/IAgentModel.h
        src/components/exporters/kinodynamicExporter/KinodynamicExporter.cpp
        src/components/exporters/kinodynamicExporter/KinodynamicExporter.h
        src/input/animationParsers/AnimationParser.h
        src/input/animationParsers/fbxParser/FbxParser.h
        src/core/exporter/HighLevelExporterTesting.cpp
        src/core/exporter/HighLevelExporterTesting.h
        src/components/solvers/SST/kinodynamic/KinodynamicSSTsolver.cpp
        src/components/solvers/SST/kinodynamic/KinodynamicSSTsolver.h
        src/components/nearestNeighbour/ompl/gnat/sst/kinodynamic/KinodynamicGNAT_SST.cpp
        src/components/nearestNeighbour/ompl/gnat/sst/kinodynamic/KinodynamicGNAT_SST.h
        src/components/nearestNeighbour/ompl/gnat/sst/kinodynamic/KinodynamicGNAT_Witness.cpp
        src/components/nearestNeighbour/ompl/gnat/sst/kinodynamic/KinodynamicGNAT_Witness.h
        src/components/sampling/positionSampling/dynamic/kinodynamic/KinodynamicBiasedSampler.cpp
        src/components/sampling/positionSampling/dynamic/kinodynamic/KinodynamicBiasedSampler.h
        src/components/costFunctions/kinodynamic/time/KinodynamicTimeSSTcostFunction.cpp
        src/components/costFunctions/kinodynamic/time/KinodynamicTimeSSTcostFunction.h
        src/components/costFunctions/astrodynamic/fuel/AstrodynamicFuelSSTcostFunction.cpp
        src/components/costFunctions/astrodynamic/fuel/AstrodynamicFuelSSTcostFunction.h
        src/components/pathGenerator/sst/kinodynamic/KinodynamicSSTpathGenerator.cpp
        src/components/pathGenerator/sst/kinodynamic/KinodynamicSSTpathGenerator.h
        src/components/nearestNeighbour/mpnn/rrt/AMPNN_RRT.h
        src/components/nearestNeighbour/mpnn/rrt/kinodynamic/KinodynamicMPNN_RRT.cpp
        src/components/nearestNeighbour/mpnn/rrt/kinodynamic/KinodynamicMPNN_RRT.h
        src/components/nearestNeighbour/mpnn/rrt/astrodynamic/AstrodynamicMPNN_RRT.cpp
        src/components/nearestNeighbour/mpnn/rrt/astrodynamic/AstrodynamicMPNN_RRT.h
        src/components/nearestNeighbour/ompl/gnat/rrt/AGNAT_RRT.h
        src/components/nearestNeighbour/ompl/gnat/rrt/kinodynamic/KinodynamicGNAT_RRT.cpp
        src/components/nearestNeighbour/ompl/gnat/rrt/kinodynamic/KinodynamicGNAT_RRT.h
        src/components/nearestNeighbour/ompl/gnat/rrt/astrodynamic/AstrodynamicGNAT_RRT.cpp
        src/components/nearestNeighbour/ompl/gnat/rrt/astrodynamic/AstrodynamicGNAT_RRT.h
        src/components/solvers/RRT/treeUtils/ANode.cpp
        src/components/solvers/RRT/treeUtils/ANode.h
        src/components/nearestNeighbour/mpnn/rrt/static/StaticMPNN_RRT.cpp
        src/components/nearestNeighbour/mpnn/rrt/static/StaticMPNN_RRT.h
        src/components/nearestNeighbour/mpnn/rrt/dynamic/DynamicMPNN_RRT.cpp
        src/components/nearestNeighbour/mpnn/rrt/dynamic/DynamicMPNN_RRT.h
)

# Main executable
add_executable(project ${SOURCE_FILES} src/main.cpp
        src/components/sampling/controlInputSampling/rotationStabilizing/StabilizingControlInputSampler.h
        src/components/sampling/controlInputSampling/rotationStabilizing/StabilizingControlInputSampler.cpp
        src/components/constraintsEnforcer/IConstraintsEnforcer.h
        src/components/constraintsEnforcer/kinodynamic/KinodynamicConstraintsEnforcer.h
        src/components/constraintsEnforcer/kinodynamic/KinodynamicConstraintsEnforcer.cpp
        src/dto/envSettings/EnvSettingsAstro.h
        src/dto/envSettings/EnvSettingsAstroRaw.h
        src/dto/poses/astrodynamic/celestialBody/CelestialBody.h
        src/utils/ScalingUtils.h
        src/components/propulsionSystem/IPropulsionSystem.h
        src/dto/poses/dynamic/kinodynamic/burstControlInput/BurstControlInput.h
        src/dto/poses/dynamic/kinodynamic/burstControlInput/BurstControlInput.cpp
        src/components/propulsionSystem/burst/BurstPropulsionSystem.h
        src/components/propulsionSystem/burst/BurstPropulsionSystem.cpp
        src/components/solvers/utils/statePropagators/IStatePropagator.h
        src/components/solvers/utils/statePropagators/StatePropagator.cpp
        src/components/solvers/utils/statePropagators/StatePropagator.h
        src/components/solvers/utils/statePropagators/KinodynamicStatePropagator.h
        src/components/sampling/controlInputSampling/burst/BurstControlInputSampler.h
        src/dto/poses/astrodynamic/spaceshipState/SpaceshipState.cpp
        src/dto/poses/astrodynamic/spaceshipState/SpaceshipState.h
        src/components/physics/physicsSimulator/PhysicsSimulator.h
        src/components/physics/internalForcesComputer/InternalForcesComputer.h
        src/components/physics/externalForceComputer/ExternalForcesComputer.h
        src/components/physics/totalForce/TotalForce.h
        src/components/physics/interactions/IInteraction.h
        src/components/physics/interactions/GravityInteraction.h
        src/components/physics/physicsSimulator/IPhysicsSimulator.h
        src/dto/totalAcceleration/TotalAcceleration.h
        src/components/physics/forceToAccelerationConverter/IForceToAccelerationConverter.h
        src/components/physics/forceToAccelerationConverter/ForceToAccelerationConverter.h
        src/components/physics/internalForcesComputer/IInternalForcesComputer.h
        src/components/physics/externalForceComputer/IExternalForcesComputer.h
        src/components/solvers/RRT/dynamic/astrodynamic/AstrodynamicRRTsolver.cpp
        src/components/solvers/RRT/dynamic/astrodynamic/AstrodynamicRRTsolver.h
        src/components/collisionHandlers/astrodynamic/AstrodynamicCollisionHandler.cpp
        src/components/collisionHandlers/astrodynamic/AstrodynamicCollisionHandler.h
        src/components/pathGenerator/tree/dynamic/astrodynamic/AstrodynamicPathGenerator.h
        src/components/sampling/positionSampling/dynamic/astrodynamic/AstrodynamicBiasedRandomSampler.cpp
        src/components/sampling/positionSampling/dynamic/astrodynamic/AstrodynamicBiasedRandomSampler.h
        src/components/exporters/astrodynamicExporter/AstrodynamicExporter.cpp
        src/components/exporters/astrodynamicExporter/AstrodynamicExporter.h
        src/components/terminationConditions/astrodynamic/AstrodynamicTerminationCondition.cpp
        src/components/terminationConditions/astrodynamic/AstrodynamicTerminationCondition.h
        src/components/interpolators/AInterpolator.h
        src/components/interpolators/astrodynamic/AstrodynamicInterpolator.cpp
        src/components/interpolators/astrodynamic/AstrodynamicInterpolator.h
        src/components/sampling/controlInputSampling/burst/kinodynamic/KinodynamicBurstSampler.cpp
        src/components/sampling/controlInputSampling/burst/kinodynamic/KinodynamicBurstSampler.h
        src/components/sampling/controlInputSampling/burst/astrodynamic/AstrodynamicBurstSampler.cpp
        src/components/sampling/controlInputSampling/burst/astrodynamic/AstrodynamicBurstSampler.h
        src/components/constraintsEnforcer/astrodynamic/AstrodynamicConstraintsEnforcer.cpp
        src/components/constraintsEnforcer/astrodynamic/AstrodynamicConstraintsEnforcer.h
        src/components/solvers/utils/statePropagators/AstrodynamicStatePropagator.h
        src/components/physics/physicsSimulator/AstrodynamicPhysicsSimulator.h
        src/components/physics/internalForcesComputer/AstrodynamicInternalForcesComputer.h
        src/components/physics/externalForceComputer/AstrodynamicExternalForcesComputer.h
        src/components/physics/forceToAccelerationConverter/AstrodynamicForceToAccelerationConverter.h
        src/components/physics/interactions/AstrodynamicGravityInteraction.h
        src/components/fuelSystem/IFuelSystem.h
        src/dto/fuelState/FuelState.h
        src/components/fuelSystem/FuelSystem.h
        src/components/fuelSystem/FuelSystem.cpp
        src/components/sampling/positionSampling/dynamic/astrodynamic/BiasedSphericalBoundariesSampler/BiasedSphericalBoundariesSampler.cpp
        src/components/sampling/positionSampling/dynamic/astrodynamic/BiasedSphericalBoundariesSampler/BiasedSphericalBoundariesSampler.h
        src/dto/configurationSpaceSphericalBoundaries/ConfigurationSpaceSphericalBoundaries.cpp
        src/dto/configurationSpaceSphericalBoundaries/ConfigurationSpaceSphericalBoundaries.h
        src/components/dynamicsSimulators/RK4_DynamicsSimulator.h
        src/components/dynamicsSimulators/Euler_DynamicsSimulator.h
        src/components/planner/IPlanner.h
        src/components/planner/kinodynamic/KinodynamicPlanner.cpp
        src/components/planner/kinodynamic/KinodynamicPlanner.h
        src/components/planner/astrodynamic/AstrodynamicPlanner.cpp
        src/components/planner/astrodynamic/AstrodynamicPlanner.h
        src/components/dynamicsSimulators/kinodynamic/RK4_KinodynamicSimulator.cpp
        src/components/dynamicsSimulators/kinodynamic/RK4_KinodynamicSimulator.h
        src/components/dynamicsSimulators/astrodynamic/RK4_AstrodynamicSimulator.cpp
        src/components/dynamicsSimulators/astrodynamic/RK4_AstrodynamicSimulator.h
        src/components/dynamicsSimulators/astrodynamic/EulerAstrodynamicSimulator.cpp
        src/components/dynamicsSimulators/astrodynamic/EulerAstrodynamicSimulator.h
        src/components/derivator/IDerivator.h
        src/components/derivator/kinodynamic/KinodynamicDerivator.cpp
        src/components/derivator/kinodynamic/KinodynamicDerivator.h
        src/components/derivator/astrodynamic/AstrodynamicDerivator.cpp
        src/components/derivator/astrodynamic/AstrodynamicDerivator.h
)

target_sources(project PRIVATE
        ${CMAKE_SOURCE_DIR}/../libraries/ompl_nn/ompl/util/src/RandomNumbers.cpp
        ${CMAKE_SOURCE_DIR}/../libraries/ompl_nn/ompl/util/src/Console.cpp
        ${CMAKE_SOURCE_DIR}/../libraries/ompl_nn/ompl/util/src/ProlateHyperspheroid.cpp
        ${CMAKE_SOURCE_DIR}/../libraries/ompl_nn/ompl/util/src/GeometricEquations.cpp
        ${CMAKE_SOURCE_DIR}/../libraries/ompl_nn/ompl/util/src/String.cpp
        ${CMAKE_SOURCE_DIR}/../libraries/ompl_nn/ompl/util/src/Time.cpp
        ${CMAKE_SOURCE_DIR}/../libraries/ompl_nn/ompl/util/src/PPM.cpp
)

target_include_directories(project PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${EIGEN3_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/../libraries/rapid
        ${CMAKE_SOURCE_DIR}/../libraries/mpnn
        ${CMAKE_SOURCE_DIR}/../libraries/fbx_sdk/include
        ${CMAKE_SOURCE_DIR}/../libraries/spdlog/include
        ${CMAKE_SOURCE_DIR}/../libraries/ompl_nn
        ${CMAKE_SOURCE_DIR}/../libraries/boost
)
target_link_directories(project PRIVATE
        ${FBX_LIB_DIR}
        ${CMAKE_SOURCE_DIR}/../libraries/boost/stage/lib)
target_link_libraries(project PRIVATE
        ${RAPID_STATIC_LIB}
        ${MPNN_STATIC_LIB}
        jsoncpp
        ${SPDLOG_STATIC_LIB}
        fbxsdk
        Eigen3::Eigen
)


# Test executable
#(runTests ${SOURCE_FILES} test/DynamicsSimulatorTest.cpp)
#target_include_directories(runTests PRIVATE
#        ${CMAKE_SOURCE_DIR}/src
#        ${EIGEN3_INCLUDE_DIR}
#        ${CMAKE_SOURCE_DIR}/../libraries/rapid
#        ${CMAKE_SOURCE_DIR}/../libraries/mpnn
#        ${CMAKE_SOURCE_DIR}/../libraries/fbx_sdk/include
#        ${CMAKE_SOURCE_DIR}/../libraries/spdlog/include
#        ${CMAKE_SOURCE_DIR}/../libraries/gtest/googletest/include
#)
#target_link_directories(runTests PRIVATE ${FBX_LIB_DIR})
#target_link_libraries(runTests PRIVATE
#        ${RAPID_STATIC_LIB}
#        ${MPNN_STATIC_LIB}
#        jsoncpp
#        ${SPDLOG_STATIC_LIB}
#        fbxsdk
#        Eigen3::Eigen
#        ${GTEST_STATIC_LIB}
#        ${GTEST_MAIN_STATIC_LIB}
#        pthread  # Required for Google Test on Unix-like systems
#)

# Enable testing
enable_testing()
add_test(NAME DynamicsSimulatorTests COMMAND runTests)