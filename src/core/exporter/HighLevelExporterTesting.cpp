//
// Created by arseniy on 9.5.25.
//

#include "HighLevelExporterTesting.h"

#include <fstream>

void HighLevelExporterTesting::exportOutput(IComponentManager *componentManager, ExecutorOutput executorOutput)
{
    exprotTestData(executorOutput);
}

void HighLevelExporterTesting::exprotTestData(ExecutorOutput executorOutput)
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
