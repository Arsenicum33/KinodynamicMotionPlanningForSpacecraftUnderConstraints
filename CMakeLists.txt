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

# Add your source files (adjusted to use the src/ directory)
add_executable(project
    src/main.cpp
        src/components/solvers/treeSolvers/AbstractTreeSolver.cpp
        src/components/solvers/treeSolvers/RRT*/RrtStarSolver.cpp
        src/components/solvers/treeSolvers/RRT/RRTsolver.cpp
    src/poses/static/PoseMath.cpp
    src/poses/static/Pose.cpp
    src/fileParsers/meshParsers/RapidObjMeshParser.cpp
    src/ConfigurationSpaceBoundaries.cpp
        src/components/solvers/configs/SolverFactory.cpp
        src/components/solvers/configs/AbstractSolverConfig.cpp
        src/components/solvers/configs/treeSolverConfigs/AbstractTreeSolverConfig.cpp
        src/components/solvers/configs/treeSolverConfigs/RRT*/RrtStarSolverConfig.cpp
        src/components/solvers/configs/treeSolverConfigs/RRT/RRTsolverConfig.cpp
        src/components/exporters/DefaultExporter.cpp
        src/input/InputParser.cpp
        src/components/nearestNeighbour/BruteForceNNsearch.cpp
        src/components/distanceMeasurement/EuclidianDistanceMetric.cpp
        src/components/distanceMeasurement/WeightedTranslationRotationMetric.cpp
    src/poses/static/sampling/DefaultRandomSampler.cpp
    src/poses/static/sampling/BiasedRandomSampler.cpp
        src/components/collisionHandlers/RapidCollisionHandler.cpp
        src/components/nearestNeighbour/MPNNsearch.cpp
        src/components/solvers/treeSolvers/Tree.cpp
        src/components/solvers/treeSolvers/TreeNode.cpp
        src/components/pathGenerator/UniformPathGenerator.cpp
    src/poses/dynamic/Keyframe.cpp
    src/poses/dynamic/Animation.cpp
    src/poses/dynamic/DynamicObject.cpp
        src/components/solvers/configs/AbstractSolverConfig.h
        src/components/IComponent.h
        src/components/Capability.h
        src/components/ComponentRegistry.h
        src/components/IComponentFactory.h
        src/components/IComponentFactory.h
        src/components/collisionHandlers/RapidCollisionHandlerFactory.cpp
        src/components/collisionHandlers/RapidCollisionHandlerFactory.h
        src/components/ComponentRegistration.cpp
        src/input/ComponentsParser.cpp
        src/input/ComponentsParser.h
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
