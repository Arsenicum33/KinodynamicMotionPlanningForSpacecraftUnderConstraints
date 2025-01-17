//
// Created by arseniy on 31.12.24.
//
#pragma once

#include <poses/static/PoseMath.h>

#include "FbxParser.h"
#include <iostream>
#include <fstream>

template <typename MeshType>
std::unique_ptr<DynamicObject<MeshType>> FbxParser<MeshType>::parse(const std::string& filepath)
{
    FbxScene* scene = initializeScene(filepath);

    auto animation = extractAnimation(scene);

    std::string objFilepath = createTempObjFile(scene);

    auto meshVector = meshParser->parse(objFilepath);

    if (meshVector.size() != 1)
    {
        throw std::invalid_argument("FbxParser: expected 1 mesh, but got " + meshVector.size());
    }

    auto mesh = std::move(meshVector[0]);

    return std::make_unique<DynamicObject<MeshType>>(std::move(animation), std::move(mesh));
}

template<typename MeshType>
std::unique_ptr<Animation> FbxParser<MeshType>::extractAnimation(FbxScene* scene)
{
    std::vector<Keyframe> keyframes;
    FbxNode* rootNode = scene->GetRootNode();
    if (!rootNode)
    {
        fbxManager->Destroy();
        throw std::runtime_error("FBX file does not have a root node.");
    }

    std::vector<FbxNode*> meshes = getSceneMeshes(rootNode);
    if (meshes.size() != 1)
    {
        fbxManager->Destroy();
        throw std::runtime_error("FbxParser: expected 1 mesh, but got " + meshes.size());
    }
    FbxNode* mesh = meshes[0];

    FbxAnimStack* animStack = scene->GetSrcObject<FbxAnimStack>(0);
    if (!animStack)
    {
        fbxManager->Destroy();
        throw std::runtime_error("Failed to get FbxAnimStack");
    }

    FbxTimeSpan span = animStack->GetLocalTimeSpan();
    FbxTime start = span.GetStart();
    FbxTime stop = span.GetStop();

    double numericalFrameRate = FbxTime::GetFrameRate(frameRate);
    FbxTime dt;
    dt.SetSecondDouble(1.0 / numericalFrameRate);
    int frameNumber = 1;
    double normalizationConstant = 100.0;
    for (FbxTime t = start; t <= stop;t+=dt, frameNumber++)
    {
        FbxAMatrix globalTransform = mesh->EvaluateGlobalTransform(t);
        FbxVector4 translation = globalTransform.GetT();
        FbxVector4 rotation = globalTransform.GetR();
        keyframes.emplace_back(
            std::array<double, 3>{translation[0]/normalizationConstant, translation[1]/normalizationConstant, translation[2]/normalizationConstant},
            PoseMath::eulerToRotationMatrix(std::array<double, 3>{rotation[0], rotation[1], rotation[2]}), // Replace with actual quaternion logic
            frameNumber);
    }

    return std::make_unique<Animation>(keyframes);
}

template<typename MeshType>
std::string FbxParser<MeshType>::createTempObjFile(FbxScene* scene)
{
    std::ofstream objFile(tempObjFile);
    if (!objFile.is_open())
    {
        fbxManager->Destroy();
        throw std::runtime_error("Failed to open temporary .obj file for writing.");
    }

    FbxNode* rootNode = scene->GetRootNode();
    if (!rootNode)
    {
        fbxManager->Destroy();
        throw std::runtime_error("FBX file does not have a root node.");
    }


    std::vector<FbxNode*> meshes = getSceneMeshes(rootNode);
    if (meshes.size() != 1)
    {
        fbxManager->Destroy();
        throw std::runtime_error("FbxParser: expected 1 mesh, but got " + meshes.size());
    }
    FbxNode* meshNode = meshes[0];

    FbxMesh* mesh = meshNode->GetMesh();

    FbxGeometryConverter geometryConverter(fbxManager);
    FbxMesh* triangulatedMesh = FbxCast<FbxMesh>(geometryConverter.Triangulate(mesh, true));

    FbxAMatrix globalTransform = meshNode->EvaluateGlobalTransform();
    FbxVector4 scaling = globalTransform.GetS();
    double normalizationConstant = 100.0;
    for (int v = 0; v < triangulatedMesh->GetControlPointsCount(); v++)
    {
        FbxVector4 vertex = triangulatedMesh->GetControlPointAt(v);
        objFile << "v " << vertex[0]*scaling[0]/normalizationConstant << " " << vertex[1]*scaling[1]/normalizationConstant << " " << vertex[2]*scaling[2]/normalizationConstant << "\n";
    }

    for (int p = 0; p < triangulatedMesh->GetPolygonCount(); ++p)
    {
        objFile << "f";
        for (int j = 0; j < triangulatedMesh->GetPolygonSize(p); ++j)
        {
            objFile << " " << (triangulatedMesh->GetPolygonVertex(p, j) + 1);
        }
        objFile << "\n";
    }

    objFile.close();
    fbxManager->Destroy();

    return tempObjFile;
}

template<typename MeshType>
void FbxParser<MeshType>::printNodeHierarchy(FbxNode* node, int depth)
{
    if (!node) return;

    // Print the node name with indentation
    std::string indent(depth * 2, ' ');
    std::cout << indent << "Node: " << node->GetName() << std::endl;

    // Check if the node has an attribute (e.g., mesh, light, camera)
    FbxNodeAttribute* attribute = node->GetNodeAttribute();
    if (attribute) {
        std::cout << indent << "  Attribute Type: ";
        switch (attribute->GetAttributeType()) {
            case FbxNodeAttribute::eMesh: std::cout << "Mesh"; break;
            case FbxNodeAttribute::eLight: std::cout << "Light"; break;
            case FbxNodeAttribute::eCamera: std::cout << "Camera"; break;
            case FbxNodeAttribute::eSkeleton: std::cout << "Skeleton"; break;
            default: std::cout << "Other"; break;
        }
        std::cout << std::endl;
    }

    // Recurse into children
    for (int i = 0; i < node->GetChildCount(); ++i) {
        printNodeHierarchy(node->GetChild(i), depth + 1);
    }
}

template<typename MeshType>
std::vector<FbxNode*> FbxParser<MeshType>::getSceneMeshes(FbxNode *node)
{
    std::vector<FbxNode*> result;
    FbxNodeAttribute* attribute = node->GetNodeAttribute();
    if (attribute && attribute->GetAttributeType() == FbxNodeAttribute::eMesh)
    {
        result.push_back(node);
    }
    for (int i = 0; i < node->GetChildCount(); i++)
    {
        std::vector<FbxNode*> childsMeshes = getSceneMeshes(node->GetChild(i));
        result.insert(result.end(), childsMeshes.begin(), childsMeshes.end());
    }
    return result;
}

template<typename MeshType>
FbxScene* FbxParser<MeshType>::initializeScene(const std::string &filepath)
{
    fbxManager = FbxManager::Create();
    FbxIOSettings* ios = FbxIOSettings::Create(fbxManager, IOSROOT);
    fbxManager->SetIOSettings(ios);

    FbxImporter* importer = FbxImporter::Create(fbxManager, "");
    if (!importer->Initialize(filepath.c_str(), -1, fbxManager->GetIOSettings()))
    {
        throw std::runtime_error("Failed to initialize FBX importer: " + std::string(importer->GetStatus().GetErrorString()));
    }

    FbxScene* scene = FbxScene::Create(fbxManager, "Scene");
    importer->Import(scene);
    importer->Destroy();
    return scene;
}
