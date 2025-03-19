//
// Created by arseniy on 31.12.24.
//

#ifndef FBXPARSER_H
#define FBXPARSER_H

#include "fbxsdk.h"

template <typename MeshType>
class FbxParser : public AnimationParser<MeshType>
{
public:
    FbxParser(MeshParser<MeshType>* parser) : meshParser(parser) {}
    std::unique_ptr<DynamicObject<MeshType>> parse(const std::string& filepath) override;
private:
    MeshParser<MeshType>* meshParser;
    FbxTime::EMode frameRate = FbxTime::eFrames24;
    FbxManager* fbxManager = nullptr;
    std::string tempObjFile = "/tmp/temp_mesh.obj";

    std::unique_ptr<Animation> extractAnimation(FbxScene* scene);

    std::string createTempObjFile(FbxScene* scene);

    void printNodeHierarchy(FbxNode* node, int depth=0);

    std::vector<FbxNode*> getSceneMeshes(FbxNode* node);

    FbxScene* initializeScene(const std::string& filepath);
};

#include "FbxParser.tpp"

#endif //FBXPARSER_H
