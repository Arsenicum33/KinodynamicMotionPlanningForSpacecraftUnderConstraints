cmake_minimum_required(VERSION 3.29)
project(PathPlanning3D)

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
        src/components/nearestNeighbour/temporalMPNN/TemporalMPNNsearch.cpp
        src/components/distanceMeasurement/temporalTotal/TemporalTransRotMetric.cpp
        src/components/interpolators/dynamic/DynamicInterpolator.cpp
        src/components/interpolators/static/StaticInterpolator.cpp
        src/components/collisionHandlers/static/StaticCollisionHandler.cpp
        src/components/collisionHandlers/dynamic/DynamicCollisionHandler.cpp
        src/components/nearestNeighbour/mpnn/static/StaticMPNNsearch.cpp
        src/components/nearestNeighbour/mpnn/dynamic/DynamicMPNNsearch.cpp
        src/components/sampling/positionSampling/dynamic/default/DynamicRandomSampler.cpp
        src/components/sampling/positionSampling/dynamic/biased/DynamicBiasedRandomSampler.cpp
        src/components/sampling/positionSampling/static/default/StaticRandomSampler.cpp
        src/components/sampling/positionSampling/static/biased/StaticBiasedRandomSampler.cpp
        src/components/sampling/positionSampling/dynamic/movingTarget/MovingTargetBiasedSampler.cpp
        src/components/terminationConditions/dynamic/DynamicTerminationCondition.cpp
        src/components/solvers/dynamic/TARRT/TAGeometricRRTsolver.cpp
        src/components/solvers/dynamic/movingTarget/MT_TARRTsolver.cpp
        src/components/solvers/static/RRT/RRTsolver.cpp
        src/dto/poses/dynamic/kinodynamic/state/State.cpp
        src/dto/poses/dynamic/kinodynamic/controlInput/ControlInput.cpp
        src/components/solvers/dynamic/kinodynamic/KinodynamicRRTsolver.cpp
        src/components/sampling/controlInputSampling/default/ControlInputSampler.cpp
        src/components/dynamicsSimulators/DynamicsSimulator.cpp
        src/components/exporters/kinodynamicExporter/DefaultKinodynamicExporter.cpp
        src/components/interpolators/kinodynamic/KinodynamicLinearInterpolator.cpp
        src/components/terminationConditions/kinodynamic/KinodynamicTerminationCondition.cpp
)

# Main executable
add_executable(project ${SOURCE_FILES} src/main.cpp
        src/components/sampling/controlInputSampling/rotationStabilizing/StabilizingControlInputSampler.cpp
        src/components/sampling/controlInputSampling/rotationStabilizing/StabilizingControlInputSampler.h
        src/components/constraintsEnforcer/IConstraintsEnforcer.h
        src/components/constraintsEnforcer/ConstraintsEnforcer.cpp
        src/components/constraintsEnforcer/ConstraintsEnforcer.h
        src/dto/envSettings/EnvSettingsAstro.h
        src/dto/envSettings/EnvSettingsAstroRaw.h
        src/dto/poses/astrodynamic/CelestialBody.cpp
        src/dto/poses/astrodynamic/CelestialBody.h)
target_include_directories(project PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${EIGEN3_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/../libraries/rapid
        ${CMAKE_SOURCE_DIR}/../libraries/mpnn
        ${CMAKE_SOURCE_DIR}/../libraries/fbx_sdk/include
        ${CMAKE_SOURCE_DIR}/../libraries/spdlog/include
)
target_link_directories(project PRIVATE ${FBX_LIB_DIR})
target_link_libraries(project PRIVATE
        ${RAPID_STATIC_LIB}
        ${MPNN_STATIC_LIB}
        jsoncpp
        ${SPDLOG_STATIC_LIB}
        fbxsdk
        Eigen3::Eigen
)

# Test executable
add_executable(runTests ${SOURCE_FILES} test/DynamicsSimulatorTest.cpp)
target_include_directories(runTests PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${EIGEN3_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/../libraries/rapid
        ${CMAKE_SOURCE_DIR}/../libraries/mpnn
        ${CMAKE_SOURCE_DIR}/../libraries/fbx_sdk/include
        ${CMAKE_SOURCE_DIR}/../libraries/spdlog/include
        ${CMAKE_SOURCE_DIR}/../libraries/gtest/googletest/include
)
target_link_directories(runTests PRIVATE ${FBX_LIB_DIR})
target_link_libraries(runTests PRIVATE
        ${RAPID_STATIC_LIB}
        ${MPNN_STATIC_LIB}
        jsoncpp
        ${SPDLOG_STATIC_LIB}
        fbxsdk
        Eigen3::Eigen
        ${GTEST_STATIC_LIB}
        ${GTEST_MAIN_STATIC_LIB}
        pthread  # Required for Google Test on Unix-like systems
)

# Enable testing
enable_testing()
add_test(NAME DynamicsSimulatorTests COMMAND runTests)