// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef HIGHLEVELEXPORTERTESTING_H
#define HIGHLEVELEXPORTERTESTING_H
#include <unordered_set>

#include "IHighLevelExporter.h"
#include "components/solvers/RRT/treeUtils/ANode.h"


class HighLevelExporterTesting : public IHighLevelExporter
{
public:
    HighLevelExporterTesting(const std::string& outputFilepath) : outputFilepath(outputFilepath){}
    void exportOutput(IComponentManager *componentManager, ExecutorOutput executorOutput) override;
    void exportTestData(ExecutorOutput executorOutput, IComponentManager *componentManager);
private:
    std::string outputFilepath;


};



#endif //HIGHLEVELEXPORTERTESTING_H
