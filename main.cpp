#include <iostream>

#include "ConfigurationSpaceBoundaries.h"
#include "meshParsers/ObjMeshParser.h"
#include "solvers/AbstractSolver.h"
#include "solvers/treeSolvers/RRT/RRTsolver.h"
#include <filesystem>

#include "InputParser.h"
#include "exporters/DefaultExporter.h"
#include "solvers/configs/SolverFactory.h"

#define ALG_CONFIG_FILEPATH "../algorithm_config.json"
#define OUTPUT_FILENAME "output.json"



int main(int argc, char* argv[])
{
    InputParser parser(argc, argv, argc!=2);
    EnvSettings envSettings = parser.getEnvSettings();

    ObjMeshParser objMesh;
    auto obstacles = objMesh.parse(envSettings.obstaclesFilepath);
    auto agent = std::move(objMesh.parse(envSettings.agentFilepath)[0]);


    auto solver = SolverFactory::createSolverFromConfig(ALG_CONFIG_FILEPATH, envSettings);
    auto poses = solver->solve(obstacles, agent, envSettings.startPose, envSettings.endPose);
    auto exporter = DefaultExporter(OUTPUT_FILENAME);
    exporter.exportPoses(poses);
    return 0;
}

