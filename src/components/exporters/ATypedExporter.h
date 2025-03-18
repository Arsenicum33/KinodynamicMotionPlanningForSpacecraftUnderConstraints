//
// Created by arseniy on 23.10.24.
//

#ifndef ATYPEDEXPORTER_H
#define ATYPEDEXPORTER_H

#include <string>
#include <vector>

#include "IPositionExporter.h"
#include "../../poses/static/Pose.h"
#include "components/IComponent.h"

template <typename PositionType>
class ATypedExporter : public IPositionExporter
{
public:
    ATypedExporter(const std::string& filename) : filename(filename) {};

    ComponentType getType() const override { return ComponentType::Exporter; }

    void exportPositions(std::vector<std::any> positions) const final;

    virtual void exportPositionsTyped(std::vector<PositionType> positions) const = 0;

protected:
    std::string filename;
};

template<typename PositionType>
void ATypedExporter<PositionType>::exportPositions(std::vector<std::any> positions) const
{
    std::vector<PositionType> positionsTyped;
    for (auto it = positions.begin(); it != positions.end(); ++it)
    {
        positionsTyped.push_back(std::any_cast<PositionType>(*it));
    }
    exportPositionsTyped(positionsTyped);
}


#endif //ATYPEDEXPORTER_H
