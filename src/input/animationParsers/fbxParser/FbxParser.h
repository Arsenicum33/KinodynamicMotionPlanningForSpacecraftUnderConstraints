// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef FBXPARSER_H
#define FBXPARSER_H

#include <input/animationParsers/AnimationParser.h>

#include "fbxsdk.h"

template <typename MeshType>
class FbxParser : public AnimationParser<MeshType>
{
public:
    FbxParser(MeshParser<MeshType>* parser) : meshParser(parser) {}

    std::shared_ptr<DynamicObject<MeshType>> parse(const std::string &filepath) override;
private:
    MeshParser<MeshType>* meshParser;
    FbxTime::EMode frameRate = FbxTime::eFrames24;
    FbxManager* fbxManager = nullptr;
    std::string tempObjFile = "/tmp/temp_mesh.obj";

    std::shared_ptr<Animation> extractAnimation(FbxScene* scene);

    std::string createTempObjFile(FbxScene* scene);

    void printNodeHierarchy(FbxNode* node, int depth=0);

    std::vector<FbxNode*> getSceneMeshes(FbxNode* node);

    FbxScene* initializeScene(const std::string& filepath);
};

#include "FbxParser.tpp"

#endif //FBXPARSER_H
