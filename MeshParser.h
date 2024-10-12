//
// Created by arseniy on 23.9.24.
//

#ifndef MESHPARSER_H
#define MESHPARSER_H
#include <memory>
#include <RAPID.H>
#include <string>


class MeshParser
{
public:
    virtual ~MeshParser() = default;
    virtual std::vector<std::unique_ptr<RAPID_model>> parse(const std::string& filename) = 0;
};


#endif //MESHPARSER_H
