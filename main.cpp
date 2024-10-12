#include <iostream>

#include "ObjMeshParser.h"

int main()
{
    ObjMeshParser objMesh;
    auto obstacles = objMesh.parse("/home/arseniy/Bachaerlors_thesis/Semester_project/blender/models/two_cubes.obj");
    auto agent = std::move(objMesh.parse("/home/arseniy/Bachaerlors_thesis/Semester_project/blender/models/cube.obj")[0]);
    double T1[3] = {0.0,0.0,0.0};
    double T2[3] = {0.0,0.0,0.0};
    double R1[3][3] = {{1.0,0.0,0.0},{0.0,1.0,0.0}, {0.0,0.0,1.0}};
    double R2[3][3] = {{1.0,0.0,0.0},{0.0,1.0,0.0}, {0.0,0.0,1.0}};
    RAPID_Collide(R1, T1, obstacles[1].get(), R2, T2, agent.get());
    std::cout << RAPID_num_contacts;
    return 0;
}
