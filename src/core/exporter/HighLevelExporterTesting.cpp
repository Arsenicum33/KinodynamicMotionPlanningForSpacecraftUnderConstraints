//
// Created by arseniy on 9.5.25.
//

#include "HighLevelExporterTesting.h"

#include <fstream>
#include <queue>
#include <utility>
#include <components/solvers/ISolver.h>

void HighLevelExporterTesting::exportOutput(IComponentManager *componentManager, ExecutorOutput executorOutput)
{

    exportTestData(executorOutput, componentManager);
}



void HighLevelExporterTesting::exportTestData(ExecutorOutput executorOutput,IComponentManager *componentManager )
{
    Json::Value root;

    root["iterations"] = executorOutput.totalIterations;
    root["runtime"] = executorOutput.totalTime;

    std::shared_ptr<IComponent> solverComponent = componentManager->getComponent(ComponentType::Solver);
    try
    {
        std::shared_ptr<ISolver> solver = std::dynamic_pointer_cast<ISolver>(solverComponent);
        const auto& iterationsToNodes = solver->getIterationsToNodes();
        const auto& iteratationsToRuntime = solver->getIterationsToRuntime();
        Json::Value iterationsToNodesToRuntimeJson(Json::arrayValue);
        for (int i = 0; i < iteratationsToRuntime.size(); i++)
        {
            Json::Value jsonTuple(Json::arrayValue);
            jsonTuple.append(iterationsToNodes[i].first);
            jsonTuple.append(iterationsToNodes[i].second);
            jsonTuple.append(iteratationsToRuntime[i].second);
            iterationsToNodesToRuntimeJson.append(jsonTuple);
        }
        root["iterationsToNodesToRuntime"] = iterationsToNodesToRuntimeJson;
    }
    catch (std::exception& e)
    {
        spdlog::error(e.what());
        throw e;
    }

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


