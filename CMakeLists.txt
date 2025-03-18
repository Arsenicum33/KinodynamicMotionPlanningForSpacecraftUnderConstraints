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
    src/poses/static/PoseMath.cpp
    src/poses/static/Pose.cpp
    src/fileParsers/meshParsers/RapidObjMeshParser.cpp
        src/dto/ConfigurationSpaceBoundaries.cpp
        src/components/exporters/defaultExporter/DefaultExporter.cpp
        src/input/InputParser.cpp
        src/components/distanceMeasurement/euclidian/EuclidianDistanceMetric.cpp
        src/components/distanceMeasurement/defaultSpatial/DefaultSpatialDistanceMetric.cpp
        src/components/pathGenerator/tree/uniform/UniformPathGenerator.cpp
    src/poses/dynamic/Keyframe.cpp
        src/poses/dynamic/DynamicObject.cpp
        src/components/IComponent.h
        src/components/capabilities/Capability.h
        src/components/registration/ComponentRegistry.h
        src/components/registration/ComponentRegistration.cpp
        src/input/ComponentsParser.cpp
        src/input/ComponentsParser.h
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
        src/core/reader/IReaderFactory.h
        src/core/reader/DefaultReaderFactory.cpp
        src/core/reader/DefaultReaderFactory.h
        src/components/solvers/ASolver.h
        src/components/collisionHandlers/dynamic/IDynamicCollisionHandler.h
        src/poses/dynamic/KeyframeMath.cpp
        src/poses/dynamic/KeyframeMath.h
        src/components/sampling/ISampler.h
        src/components/pathGenerator/tree/dynamic/DefaultDynamicPathGenerator.cpp
        src/components/pathGenerator/tree/dynamic/DefaultDynamicPathGenerator.h
        src/components/exporters/dynamicExporter/DefaultDynamicExporter.cpp
        src/components/exporters/dynamicExporter/DefaultDynamicExporter.h
        src/components/capabilities/manager/CapabilityManager.h
        src/components/capabilities/manager/CapabilityManager.cpp
        src/dto/EnvSettingsRaw.h
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
        src/components/solvers/newHierarchy/ISolver.h
        src/components/solvers/newHierarchy/ARRTsolver.h
        src/components/collisionHandlers/static/StaticCollisionHandler.cpp
        src/components/collisionHandlers/static/StaticCollisionHandler.h
        src/components/collisionHandlers/static/IStaticCollisionHandler.h
        src/components/collisionHandlers/dynamic/DynamicCollisionHandler.cpp
        src/components/collisionHandlers/dynamic/DynamicCollisionHandler.h
        src/components/solvers/newHierarchy/static/RRT/RRTsolver.cpp
        src/components/solvers/newHierarchy/static/RRT/RRTsolver.h
        src/components/solvers/newHierarchy/dynamic/TARRT/TARRTsolver.cpp
        src/components/solvers/newHierarchy/dynamic/TARRT/TARRTsolver.h
        src/components/solvers/newHierarchy/dynamic/movingTarget/MT_TARRTsolver.cpp
        src/components/solvers/newHierarchy/dynamic/movingTarget/MT_TARRTsolver.h
        src/components/exporters/ATypedExporter.h
        src/components/exporters/IPositionExporter.h
        src/components/nearestNeighbour/mpnn/AMPNNsearch.h
        src/components/nearestNeighbour/mpnn/StaticMPNNsearch.cpp
        src/components/nearestNeighbour/mpnn/StaticMPNNsearch.h
        src/components/nearestNeighbour/mpnn/DynamicMPNNsearch.cpp
        src/components/nearestNeighbour/mpnn/DynamicMPNNsearch.h
        src/components/sampling/ARandomSampler.h
        src/components/sampling/dynamic/default/DynamicRandomSampler.cpp
        src/components/sampling/dynamic/default/DynamicRandomSampler.h
        src/components/sampling/dynamic/default/DynamicRandomSampler.h
        src/components/sampling/dynamic/default/DynamicRandomSampler.h
        src/components/sampling/ABiasedRandomSampler.h
        src/components/sampling/dynamic/biased/DynamicBiasedRandomSampler.cpp
        src/components/sampling/dynamic/biased/DynamicBiasedRandomSampler.h
        src/components/sampling/static/default/StaticRandomSampler.cpp
        src/components/sampling/static/default/StaticRandomSampler.h
        src/components/sampling/static/biased/StaticBiasedRandomSampler.cpp
        src/components/sampling/static/biased/StaticBiasedRandomSampler.h
        src/components/sampling/dynamic/movingTarget/MovingTargetBiasedSampler.cpp
        src/components/sampling/dynamic/movingTarget/MovingTargetBiasedSampler.h
        src/components/terminationConditions/dynamic/DynamicTerminationCondition.cpp
        src/components/terminationConditions/dynamic/DynamicTerminationCondition.h
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
