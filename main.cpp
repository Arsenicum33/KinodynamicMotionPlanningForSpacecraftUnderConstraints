#include <iostream>

#include "ConfigurationSpaceBoundaries.h"
#include "solvers/AbstractSolver.h"
#include "solvers/treeSolvers/RRT/RRTsolver.h"
#include <filesystem>

#include "InputParser.h"
#include "collisionHandlers/RapidCollisionHandler.h"
#include "exporters/DefaultExporter.h"
#include "meshParsers/RapidObjMeshParser.h"
#include "poses/PoseMath.h"
#include "solvers/configs/SolverFactory.h"

#define ALG_CONFIG_FILEPATH "../algorithm_config.json"
#define OUTPUT_FILENAME "output.json"



int main(int argc, char* argv[])
{
    InputParser parser(argc, argv, argc!=2);
    EnvSettings envSettings = parser.getEnvSettings();

    RapidObjMeshParser meshParser;
    RapidCollisionHandler handler(envSettings.agentFilepath, envSettings.obstaclesFilepath, meshParser);
    std::array<double, 3> trans = {-7.1046995149447287,
            20.820020303796742,
            -10.09299168122612};
    std::array<double, 3> rot = {-2.2517959202236701,
            1.0477976569563578,
            -0.48201751134242582};
    Pose pose(trans, PoseMath::eulerToRotationMatrix(rot));
    std::array<double, 3> pose_rot = PoseMath::rotationMatrixToEuler(pose.rotation);
    handler.isPoseCollisionFree(pose);
    auto solver = SolverFactory::createSolverFromConfig(ALG_CONFIG_FILEPATH, envSettings);
    auto poses = solver->solve(envSettings.startPose, envSettings.endPose);
    bool isCorrectish = handler.arePosesCollisionFree(poses);
    auto exporter = DefaultExporter(OUTPUT_FILENAME);
    exporter.exportPoses(poses);
    return 0;
}

