cmake_minimum_required(VERSION 3.29)
project(PathPlanning3D)

# C++ Standard
set(CMAKE_CXX_STANDARD 20)

find_package(Eigen3 REQUIRED)
find_package(jsoncpp REQUIRED)

# Include the path to RAPID headers
include_directories(${CMAKE_SOURCE_DIR}/../libraries/rapid)

# Include the path to MPNN headers
include_directories(${CMAKE_SOURCE_DIR}/../libraries/mpnn)

# Set the path to RAPID build directory (containing the .a file)
set(RAPID_LIB_DIR ${CMAKE_SOURCE_DIR}/../libraries/rapid/build)

# Set the path to MPNN build directory (containing the .a file)
set(MPNN_LIB_DIR ${CMAKE_SOURCE_DIR}/../libraries/mpnn/build)

# Set RAPID static library file
set(RAPID_STATIC_LIB ${RAPID_LIB_DIR}/libRAPID.a)

# Set MPNN static library file
set(MPNN_STATIC_LIB ${MPNN_LIB_DIR}/libDNN.a)

# Set FBX include and library directories
set(FBX_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../libraries/fbx_sdk/include)
set(FBX_LIB_DIR ${CMAKE_SOURCE_DIR}/../libraries/fbx_sdk/lib/release)

include_directories(${FBX_INCLUDE_DIR})


set(SPDLOG_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../libraries/spdlog/include)
set(SPDLOG_STATIC_LIB_DIR ${CMAKE_SOURCE_DIR}/../libraries/spdlog/build)
set(SPDLOG_STATIC_LIB ${SPDLOG_STATIC_LIB_DIR}/libspdlog.a)

include_directories(${SPDLOG_INCLUDE_DIR})

add_definitions(-DSPDLOG_COMPILED_LIB)

# Add your source files (adjusted to use the src/ directory)
add_executable(project
src/main.cpp
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
src/components/IComponent.h
src/components/capabilities/Capability.h
src/components/registration/ComponentRegistry.h
src/components/registration/ComponentRegistration.h
src/input/componentsParser/ComponentsParser.cpp
src/input/componentsParser/ComponentsParser.h
src/core/Program.cpp
src/core/Program.h
src/core/reader/IReader.h
src/core/creator/IComponentManager.h
src/core/executor/IExecutor.h
src/core/validator/IValidator.h
src/core/exporter/IHighLevelExporter.h
src/core/creator/ComponentManager.cpp
src/core/creator/ComponentManager.h
src/core/executor/Executor.cpp
src/core/executor/Executor.h
src/core/exporter/HighLevelExporter.cpp
src/core/exporter/HighLevelExporter.h
src/core/reader/Reader.cpp
src/core/reader/Reader.h
src/core/validator/Validator.cpp
src/core/validator/Validator.h
src/core/reader/readerFactory/DefaultReaderFactory.cpp
src/core/reader/readerFactory/DefaultReaderFactory.h
src/components/collisionHandlers/dynamic/IDynamicCollisionHandler.h
src/components/sampling/positionSampling/IPositionSampler.h
src/components/pathGenerator/tree/dynamic/DefaultDynamicPathGenerator.h
src/components/exporters/dynamicExporter/DefaultDynamicExporter.cpp
src/components/exporters/dynamicExporter/DefaultDynamicExporter.h
src/components/capabilities/manager/CapabilityManager.h
src/components/capabilities/manager/CapabilityManager.cpp
src/dto/envSettings/EnvSettingsRaw.h
src/components/terminationConditions/ITerminationCondition.h
src/components/terminationConditions/static/StaticTerminationCondition.cpp
src/components/terminationConditions/static/StaticTerminationCondition.h
src/components/terminationConditions/movingTarget/MovingTargetTerminationCondition.cpp
src/components/terminationConditions/movingTarget/MovingTargetTerminationCondition.h
src/components/nearestNeighbour/temporalMPNN/TemporalMPNNsearch.cpp
src/components/nearestNeighbour/temporalMPNN/TemporalMPNNsearch.h
src/components/distanceMeasurement/temporalTotal/TemporalTransRotMetric.cpp
src/components/distanceMeasurement/temporalTotal/TemporalTransRotMetric.h
src/components/distanceMeasurement/temporalTotal/ITotalDistanceMetric.h
src/components/distanceMeasurement/defaultSpatial/DefaultSpatialDistanceMetric.h
src/components/ComponentType.h
src/components/pathGenerator/tree/ITreePathGenerator.h
src/components/interpolators/IInterpolator.h
src/components/interpolators/dynamic/IDynamicInterpolator.h
src/components/interpolators/dynamic/DynamicInterpolator.cpp
src/components/interpolators/dynamic/DynamicInterpolator.h
src/components/interpolators/static/IStaticInterpolator.h
src/components/interpolators/static/StaticInterpolator.h
src/components/interpolators/static/StaticInterpolator.cpp
src/components/collisionHandlers/static/StaticCollisionHandler.cpp
src/components/collisionHandlers/static/StaticCollisionHandler.h
src/components/collisionHandlers/static/IStaticCollisionHandler.h
src/components/collisionHandlers/dynamic/DynamicCollisionHandler.cpp
src/components/collisionHandlers/dynamic/DynamicCollisionHandler.h
src/components/exporters/ATypedExporter.h
src/components/exporters/IPositionExporter.h
src/components/nearestNeighbour/mpnn/AMPNNsearch.h
src/components/nearestNeighbour/mpnn/static/StaticMPNNsearch.cpp
src/components/nearestNeighbour/mpnn/static/StaticMPNNsearch.h
src/components/nearestNeighbour/mpnn/dynamic/DynamicMPNNsearch.cpp
src/components/nearestNeighbour/mpnn/dynamic/DynamicMPNNsearch.h
src/components/sampling/positionSampling/ARandomSampler.h
src/components/sampling/positionSampling/dynamic/default/DynamicRandomSampler.cpp
src/components/sampling/positionSampling/dynamic/default/DynamicRandomSampler.h
src/components/sampling/positionSampling/dynamic/default/DynamicRandomSampler.h
src/components/sampling/positionSampling/dynamic/default/DynamicRandomSampler.h
src/components/sampling/positionSampling/ABiasedRandomSampler.h
src/components/sampling/positionSampling/dynamic/biased/DynamicBiasedRandomSampler.cpp
src/components/sampling/positionSampling/dynamic/biased/DynamicBiasedRandomSampler.h
src/components/sampling/positionSampling/static/default/StaticRandomSampler.cpp
src/components/sampling/positionSampling/static/default/StaticRandomSampler.h
src/components/sampling/positionSampling/static/biased/StaticBiasedRandomSampler.cpp
src/components/sampling/positionSampling/static/biased/StaticBiasedRandomSampler.h
src/components/sampling/positionSampling/dynamic/movingTarget/MovingTargetBiasedSampler.cpp
src/components/sampling/positionSampling/dynamic/movingTarget/MovingTargetBiasedSampler.h
src/components/terminationConditions/dynamic/DynamicTerminationCondition.cpp
src/components/terminationConditions/dynamic/DynamicTerminationCondition.h
src/components/solvers/AGeometricRRTsolver.h
src/components/solvers/ISolver.h
src/components/solvers/dynamic/TARRT/TARRTsolver.cpp
src/components/solvers/dynamic/movingTarget/MT_TARRTsolver.cpp
src/components/solvers/static/RRT/RRTsolver.cpp
src/input/animationParsers/AnimationParser.h
src/input/animationParsers/fbxParser/FbxParser.h
src/input/inputParser/InputParser.h
src/core/reader/readerFactory/IReaderFactory.h
src/dto/poses/dynamic/dynamicObject/DynamicObject.h
src/dto/configurationSpaceBoundaries/ConfigurationSpaceBoundaries.h
src/dto/poses/dynamic/kinodynamic/state/State.cpp
src/dto/poses/dynamic/kinodynamic/state/State.h
src/dto/poses/dynamic/kinodynamic/controlInput/ControlInput.cpp
src/dto/poses/dynamic/kinodynamic/controlInput/ControlInput.h
src/components/solvers/dynamic/kinodynamic/AKinodynamicRRTsolver.h
src/components/solvers/ARRTsolver.h
src/components/solvers/dynamic/kinodynamic/KinodynamicRRTsolver.cpp
src/components/solvers/dynamic/kinodynamic/KinodynamicRRTsolver.h
src/components/sampling/controlInputSampling/IControlInputSampler.h
src/components/sampling/controlInputSampling/ControlInputSampler.cpp
src/components/sampling/controlInputSampling/ControlInputSampler.h
src/components/dynamicsSimulators/IDynamicsSimulator.h
src/components/dynamicsSimulators/DynamicsSimulator.cpp
src/components/dynamicsSimulators/DynamicsSimulator.h
src/utils/PhysicsUtils.h
src/components/collisionHandlers/kinodynamic/StateCollisionHandlerAdapter.h
src/components/pathGenerator/tree/dynamic/kinodynamic/KinodynamicPathGenerator.h
src/components/exporters/kinodynamicExporter/DefaultKinodynamicExporter.cpp
src/components/exporters/kinodynamicExporter/DefaultKinodynamicExporter.h
src/components/interpolators/kinodynamic/IKinodynamicInterpolator.h
src/components/interpolators/kinodynamic/KinodynamicLinearInterpolator.cpp
src/components/interpolators/kinodynamic/KinodynamicLinearInterpolator.h
src/utils/PositionUtils.h
src/utils/AnimationUtils.h
src/components/terminationConditions/kinodynamic/KinodynamicTerminationCondition.cpp
src/components/terminationConditions/kinodynamic/KinodynamicTerminationCondition.h
)

# Include headers from src/ directory
target_include_directories(project PRIVATE src/)

# Link RAPID static library
target_link_libraries(project ${RAPID_STATIC_LIB})

# Link MPNN static library
target_link_libraries(project ${MPNN_STATIC_LIB})

# Link jsoncpp library
target_link_libraries(project jsoncpp)

# Link FBX library
target_link_directories(project PRIVATE ${FBX_LIB_DIR})
target_link_libraries(project fbxsdk)


target_link_libraries(project ${SPDLOG_STATIC_LIB})