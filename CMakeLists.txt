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

# Add your source files
add_executable(project
    main.cpp
        solvers/treeSolvers/AbstractTreeSolver.cpp
        solvers/treeSolvers/RRT*/RrtStarSolver.cpp
        solvers/treeSolvers/RRT/RRTsolver.cpp
        poses/PoseMath.cpp
        poses/PoseMath.cpp
        poses/Pose.cpp
        meshParsers/RapidObjMeshParser.cpp
        solvers/treeSolvers/RRT/RRTsolver.h
        ConfigurationSpaceBoundaries.h
        ConfigurationSpaceBoundaries.cpp
        solvers/treeSolvers/TreeNode.h
        solvers/configs/SolverFactory.cpp
        solvers/configs/AbstractSolverConfig.h
        solvers/configs/treeSolverConfigs/AbstractTreeSolverConfig.h
        solvers/configs/treeSolverConfigs/RRT/RRTsolverConfig.h
        solvers/configs/treeSolverConfigs/RRT*/RrtStarSolverConfig.h
        solvers/configs/AbstractSolverConfig.cpp
        solvers/configs/treeSolverConfigs/AbstractTreeSolverConfig.cpp
        solvers/configs/treeSolverConfigs/RRT*/RrtStarSolverConfig.cpp
        solvers/configs/treeSolverConfigs/RRT/RRTsolverConfig.cpp
        solvers/configs/SolverFactory.h
        solvers/AbstractSolver.h
        solvers/AbstractSolverTemplated.h
        exporters/AbstractExporter.h
        exporters/DefaultExporter.cpp
        exporters/DefaultExporter.h
        InputParser.cpp
        InputParser.h
        EnvSettings.h
        nearestNeighbour/AbstractNearestNeighbourSearch.h
        nearestNeighbour/BruteForceNNsearch.cpp
        distanceMeasurement/IDistanceMetric.h
        distanceMeasurement/EuclidianDistanceMetric.cpp
        distanceMeasurement/EuclidianDistanceMetric.h
        distanceMeasurement/WeightedTranslationRotationMetric.cpp
        distanceMeasurement/WeightedTranslationRotationMetric.h
        poses/sampling/IPoseSampler.h
        poses/sampling/DefaultRandomSampler.cpp
        poses/sampling/DefaultRandomSampler.h
        poses/sampling/BiasedRandomSampler.cpp
        poses/sampling/BiasedRandomSampler.h
        collisionHandlers/ICollisionHandler.h
        collisionHandlers/RapidCollisionHandler.cpp
        collisionHandlers/RapidCollisionHandler.h
        meshParsers/RapidObjMeshParser.h
        nearestNeighbour/MPNNsearch.cpp
        solvers/treeSolvers/Tree.cpp
        solvers/treeSolvers/Tree.h
        solvers/treeSolvers/TreeNode.cpp
)

# Link RAPID static library
target_link_libraries(project ${RAPID_STATIC_LIB})

target_link_libraries(project ${MPNN_STATIC_LIB})

# Link jsoncpp library
target_link_libraries(project jsoncpp)