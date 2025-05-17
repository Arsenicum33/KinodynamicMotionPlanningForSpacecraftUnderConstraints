//
// Created by arseniy on 9.5.25.
//

#include "HighLevelExporterTesting.h"

#include <fstream>
#include <queue>
#include <components/solvers/ISolver.h>

void HighLevelExporterTesting::exportOutput(IComponentManager *componentManager, ExecutorOutput executorOutput)
{
    exportTestData(executorOutput);


}

void HighLevelExporterTesting::exportTestData(ExecutorOutput executorOutput)
{
    Json::Value root;

    root["iterations"] = executorOutput.totalIterations;
    root["runtime"] = executorOutput.totalTime;

    std::ofstream file(outputFilepath, std::ofstream::out);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file for writing: " + outputFilepath);
    }

    Json::StreamWriterBuilder writer;
    std::unique_ptr<Json::StreamWriter> jsonWriter(writer.newStreamWriter());
    jsonWriter->write(root, &file);
    file.close();
}

