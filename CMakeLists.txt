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
    src/solvers/treeSolvers/AbstractTreeSolver.cpp
    src/solvers/treeSolvers/RRT*/RrtStarSolver.cpp
    src/solvers/treeSolvers/RRT/RRTsolver.cpp
    src/poses/static/PoseMath.cpp
    src/poses/static/Pose.cpp
    src/fileParsers/meshParsers/RapidObjMeshParser.cpp
    src/ConfigurationSpaceBoundaries.cpp
    src/solvers/configs/SolverFactory.cpp
    src/solvers/configs/AbstractSolverConfig.cpp
    src/solvers/configs/treeSolverConfigs/AbstractTreeSolverConfig.cpp
    src/solvers/configs/treeSolverConfigs/RRT*/RrtStarSolverConfig.cpp
    src/solvers/configs/treeSolverConfigs/RRT/RRTsolverConfig.cpp
    src/exporters/DefaultExporter.cpp
    src/InputParser.cpp
    src/nearestNeighbour/BruteForceNNsearch.cpp
    src/distanceMeasurement/EuclidianDistanceMetric.cpp
    src/distanceMeasurement/WeightedTranslationRotationMetric.cpp
    src/poses/static/sampling/DefaultRandomSampler.cpp
    src/poses/static/sampling/BiasedRandomSampler.cpp
    src/collisionHandlers/RapidCollisionHandler.cpp
    src/nearestNeighbour/MPNNsearch.cpp
    src/solvers/treeSolvers/Tree.cpp
    src/solvers/treeSolvers/TreeNode.cpp
    src/pathGenerator/UniformPathGenerator.cpp
    src/poses/dynamic/Keyframe.cpp
    src/poses/dynamic/Animation.cpp
    src/poses/dynamic/DynamicObject.cpp
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
