// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef IPOSITIONEXPORTER_H
#define IPOSITIONEXPORTER_H
#include "components/IComponent.h"

class IPositionExporter : public IComponent
{
public:
    virtual void exportPositions(std::vector<std::any> positions) const = 0;
};
#endif //IPOSITIONEXPORTER_H
