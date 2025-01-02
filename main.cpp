#include <iostream>

#include "ConfigurationSpaceBoundaries.h"
#include "solvers/AbstractSolver.h"
#include "solvers/treeSolvers/RRT/RRTsolver.h"
#include <filesystem>

#include "InputParser.h"
#include "collisionHandlers/RapidCollisionHandler.h"
#include "exporters/DefaultExporter.h"
#include "fileParsers/animationParsers/FbxParser.h"
#include "fileParsers/meshParsers/RapidObjMeshParser.h"
#include "poses/static/PoseMath.h"
#include "solvers/configs/SolverFactory.h"

#define ALG_CONFIG_FILEPATH "../algorithm_config.json"
#define OUTPUT_FILENAME "output.json"

void testFbxParser(std::string filepath)
{
    RapidObjMeshParser meshParser;
    FbxParser<RAPID_model> parser(meshParser);
    auto result = parser.parse(filepath);
}

int main(int argc, char* argv[])
{
    testFbxParser("/home/arseniy/Bachaerlors_thesis/Semester_project/blender/animations/newAnim.fbx");


    InputParser parser(argc, argv, argc!=2);
    EnvSettings envSettings = parser.getEnvSettings();

    RapidObjMeshParser meshParser;
    RapidCollisionHandler handler(envSettings.agentFilepath, envSettings.obstaclesFilepath, meshParser);

    auto solver = SolverFactory::createSolverFromConfig(ALG_CONFIG_FILEPATH, envSettings);
    auto poses = solver->solve(envSettings.startPose, envSettings.endPose);
    bool isCorrectish = handler.arePosesCollisionFree(poses);
    auto exporter = DefaultExporter(OUTPUT_FILENAME);
    exporter.exportPoses(poses);
    return 0;
}

