#include <iostream>

#include "ConfigurationSpaceBoundaries.h"
#include "meshParsers/ObjMeshParser.h"
#include "solvers/AbstractSolver.h"
#include "solvers/treeSolvers/RRT/RRTsolver.h"
#include <filesystem>

#include "solvers/configs/SolverFactory.h"

int main()
{
    ObjMeshParser objMesh;
    auto obstacles = objMesh.parse("/home/arseniy/Bachaerlors_thesis/Semester_project/blender/models/two_walls_thick.obj");
    auto agent = std::move(objMesh.parse("/home/arseniy/Bachaerlors_thesis/Semester_project/blender/models/cube.obj")[0]);
    double T1[3] = {0.0,0.0,0.0};
    double T2[3] = {0.0,0.0,0.0};
    double R1[3][3] = {{1.0,0.0,0.0},{0.0,1.0,0.0}, {0.0,0.0,1.0}};
    double R2[3][3] = {{1.0,0.0,0.0},{0.0,1.0,0.0}, {0.0,0.0,1.0}};
    RAPID_Collide(R1, T1, obstacles[1].get(), R2, T2, agent.get());
    std::cout << RAPID_num_contacts;

    std::array<double, 3> translationStart = {0.0,0.0,0.0};
    std::array<double, 3> translationEnd = {30.0,0.0,0.0};
    Pose start(translationStart);
    Pose end(translationEnd);

    auto solver = SolverFactory::createSolverFromConfig("../config.json");
    auto poses = solver->solve(obstacles, agent, start, end);
    return 0;
}
