//
// Created by arseniy on 23.10.24.
//

#ifndef ATYPEDEXPORTER_H
#define ATYPEDEXPORTER_H

#include <fstream>
#include <string>
#include <vector>

#include "IPositionExporter.h"
#include "components/IComponent.h"

template <typename PositionType>
class ATypedExporter : public IPositionExporter
{
public:
    ATypedExporter(const std::string& filename) : filename(filename) {};

    ComponentType getType() const override { return ComponentType::Exporter; }

    void exportPositions(std::vector<std::any> positions) const final;

    virtual void exportPositionsTyped(std::vector<PositionType> positions) const;

    virtual Json::Value exportPositionTyped(const PositionType& position, int frame) const = 0;

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

template<typename PositionType>
void ATypedExporter<PositionType>::exportPositionsTyped(std::vector<PositionType> positions) const
{
    Json::Value root(Json::arrayValue);

    int frameCounter = 1;
    for (const PositionType& pose : positions)
    {
        Json::Value jsonPose = exportPositionTyped(pose, frameCounter);
        root.append(jsonPose);
        frameCounter++;
    }

    std::ofstream file(filename, std::ofstream::out);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file for writing: " + filename);
    }

    Json::StreamWriterBuilder writer;
    std::unique_ptr<Json::StreamWriter> jsonWriter(writer.newStreamWriter());
    jsonWriter->write(root, &file);
    file.close();
}


#endif //ATYPEDEXPORTER_H
