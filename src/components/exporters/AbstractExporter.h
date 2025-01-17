//
// Created by arseniy on 23.10.24.
//

#ifndef ABSTRACTEXPORTER_H
#define ABSTRACTEXPORTER_H

#include <string>
#include <vector>

#include "../../poses/static/Pose.h"
#include "components/IComponent.h"

template <typename T>
class AbstractExporter : public IComponent
{
public:
    AbstractExporter(const std::string& filename) : filename(filename) {};
    virtual std::vector<T> exportPoses(std::vector<T>& poses) = 0;
protected:
    std::string filename;
};


#endif //ABSTRACTEXPORTER_H
