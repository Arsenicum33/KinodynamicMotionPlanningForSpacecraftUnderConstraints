//
// Created by arseniy on 23.9.24.
//
#include <fstream>
#include "RapidObjMeshParser.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <array>

#include <RAPID.H>


std::vector<std::unique_ptr<RAPID_model>> RapidObjMeshParser::parse(const std::string &filename)
{
    clearState();

    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Could not open file " << filename << std::endl;
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    while (std::getline(file, line))
    {
        parseLine(line);
    }
    file.close();

    if (!vertices.empty() && !faces.empty())
        createRapidModel();

    return std::move(rapidModels);
}

void RapidObjMeshParser::parseLine(const std::string &line)
{
    std::istringstream iss(line);
    char prefix;
    switch (line[0])
    {
        case 'v':
        {
            std::array<double, 3> vertex {};
            iss >> prefix >> vertex[0] >> vertex[1] >> vertex[2];
            vertices.push_back(vertex);
            break;
        }
        case 'f':
        {
            iss >> prefix;
            std::vector<int> face;
            std::string vertexIndex;
            while (iss >> vertexIndex)
            {
                int index = std::stoi(vertexIndex) - 1;
                face.push_back(index);
            }
            if (face.size() != 3)
                throw std::runtime_error("Each face must consist of 3 vertices!");
            faces.push_back(face);
            break;
        }
        case 'o':
        {
            if (!vertices.empty() && !faces.empty())
                createRapidModel();
            faces.clear();
        }
        default: ;
    }
}

void RapidObjMeshParser::createRapidModel()
{
    auto model = std::make_unique<RAPID_model>();
    model->BeginModel();
    int triangleId = 0;
    for (std::vector<int>& face : faces)
    {
        std::array<double, 3> vertex1 = vertices[face[0]];
        std::array<double, 3> vertex2 = vertices[face[1]];
        std::array<double, 3> vertex3 = vertices[face[2]];
        model->AddTri(vertex1.data(), vertex2.data(), vertex3.data(), triangleId);
        triangleId++;
    }
    model->EndModel();
    rapidModels.push_back(std::move(model));
}

void RapidObjMeshParser::clearState()
{
    vertices.clear();
    faces.clear();
    rapidModels.clear();
}


