// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef MESHPARSER_H
#define MESHPARSER_H
#include <memory>
#include <RAPID.H>
#include <string>
#include <vector>

template <typename MeshType>
class MeshParser
{
public:
    virtual ~MeshParser() = default;
    virtual std::vector<std::shared_ptr<MeshType>> parse(const std::string& filename) = 0;
};


#endif //MESHPARSER_H
