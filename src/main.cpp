#include <iostream>

#include "ConfigurationSpaceBoundaries.h"
#include "components/solvers/AbstractSolver.h"
#include "components/solvers/treeSolvers/RRT/RRTsolver.h"
#include <filesystem>

#include "input/InputParser.h"
#include "components/collisionHandlers/RapidCollisionHandler.h"
#include "components/exporters/DefaultExporter.h"
#include "fileParsers/animationParsers/FbxParser.h"
#include "fileParsers/meshParsers/RapidObjMeshParser.h"
#include "poses/static/PoseMath.h"
#include "components/solvers/configs/SolverFactory.h"
#include "input/ComponentsParser.h"

#define ALG_CONFIG_FILEPATH "../algorithm_config.json"
#define OUTPUT_FILENAME "output.json"
#define COMPONENTS_CONFIG_FILEPATH "../components.json"
void testFbxParser(std::string filepath)
{
    RapidObjMeshParser meshParser;
    FbxParser<RAPID_model> parser(meshParser);
    auto result = parser.parse(filepath);
}

int main(int argc, char* argv[])
{
    /*std::unordered_map<std::string, std::any> data = {
        {"agentFilepath", std::string("/home/arseniy/Bachaerlors_thesis/Semester_project/blender/models/worm.obj")},
        {"obstacleFilepath", std::string("/home/arseniy/Bachaerlors_thesis/Semester_project/blender/models/arena.obj")},
        {"parser", new RapidObjMeshParser()}
    };*/

    ComponentsParser componentsParser(COMPONENTS_CONFIG_FILEPATH);
    auto componentsConfig = componentsParser.getComponents();
    IComponent* createdComponent;
    for (auto component : componentsConfig)
    {
        createdComponent = ComponentRegistry<IComponent>::create(component.type, component.config);
    }
    std::string name = "RapidCollisionHandler";
    //auto x = ComponentRegistry<IComponent>::create(name, data);
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

