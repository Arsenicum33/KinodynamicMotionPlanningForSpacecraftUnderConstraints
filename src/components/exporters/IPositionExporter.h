//
// Created by arseniy on 18.3.25.
//

#ifndef IPOSITIONEXPORTER_H
#define IPOSITIONEXPORTER_H
#include "components/IComponent.h"

class IPositionExporter : public IComponent
{
public:
    virtual void exportPositions(std::vector<std::any> positions) const = 0;
};
#endif //IPOSITIONEXPORTER_H
