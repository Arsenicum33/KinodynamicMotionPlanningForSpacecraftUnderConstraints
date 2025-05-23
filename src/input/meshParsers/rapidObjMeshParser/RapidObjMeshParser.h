// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef OBJMESHPARSER_H
#define OBJMESHPARSER_H
#include <vector>
#include <input/meshParsers/MeshParser.h>


class RapidObjMeshParser : public MeshParser<RAPID_model>
{
public:
    std::vector<std::shared_ptr<RAPID_model>> parse(const std::string &filename) override;
private:
    void parseLine(const std::string &line);
    void createRapidModel();
    void clearState();

    std::vector<std::array<double, 3>> vertices;
    std::vector<std::vector<int>> faces;
    std::vector<std::shared_ptr<RAPID_model>> rapidModels;
};

#endif //OBJMESHPARSER_H
