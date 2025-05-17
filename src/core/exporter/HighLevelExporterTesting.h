//
// Created by arseniy on 9.5.25.
//

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
    void exportTestData(ExecutorOutput executorOutput);

private:
    std::string outputFilepath;


};


#endif //HIGHLEVELEXPORTERTESTING_H
