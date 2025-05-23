// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#include "HighLevelExporter.h"

#include <queue>
#include <components/collisionHandlers/ICollisionHandler.h>
#include <components/exporters/ATypedExporter.h>
#include <components/solvers/ISolver.h>

void HighLevelExporter::exportOutput(IComponentManager* componentManager,ExecutorOutput executorOutput)
{
     std::shared_ptr<IComponent> exporterComponent = componentManager->getComponent(ComponentType::Exporter);
     std::shared_ptr<IPositionExporter> exporter = std::dynamic_pointer_cast<IPositionExporter>(exporterComponent);
     exporter->exportPositions(executorOutput.path);

     if (exportSolution)
     {
          std::shared_ptr<IComponent> solverComponent = componentManager->getComponent(ComponentType::Solver);
          try
          {
               std::shared_ptr<ISolver> solver = std::dynamic_pointer_cast<ISolver>(solverComponent);
               std::vector<std::shared_ptr<ANode>> nodes = solver->getData();
               auto edges = getSolverTreeEdges(nodes);
               exportSolutionGraph(nodes, edges);
          }
          catch (std::exception& e)
          {
               spdlog::error(e.what());
               throw e;
          }
     }
}

std::unordered_set<Edge, EdgeHash> HighLevelExporter::getSolverTreeEdges(
    std::vector<std::shared_ptr<ANode>> nodes)
{
     if (nodes.empty())
     {
          return std::unordered_set<Edge, EdgeHash>();
     }
     std::unordered_set<Edge, EdgeHash> result;
     std::shared_ptr<ANode> root = nodes[0];
     std::queue<std::shared_ptr<ANode>> queue;
     queue.push(root);
     while (!queue.empty())
     {
          auto node = queue.front();
          queue.pop();
          auto children = node->getChildren();
          for (auto child : children)
          {
               result.insert(Edge(node->getIndex(), child->getIndex()));
               queue.push(child);
          }
     }
     return result;
}

void HighLevelExporter::exportSolutionGraph(std::vector<std::shared_ptr<ANode>> &nodes,
    std::unordered_set<Edge, EdgeHash> &edges)
{
     Json::Value root;

     Json::Value jsonNodes(Json::arrayValue);
     for (auto node : nodes)
     {
          Json::Value jsonNode;
          jsonNode["index"] = node->getIndex();
          Json::Value nodePosition(Json::arrayValue);
          for (int coord : node->getStateRepresentation()->translation)
          {
               nodePosition.append(coord);
          }
          jsonNode["position"] = nodePosition;
          jsonNodes.append(jsonNode);
     }
     Json::Value jsonEdges(Json::arrayValue);
     for (auto edge : edges)
     {
          Json::Value jsonEdge(Json::arrayValue);
          jsonEdge.append(edge.first);
          jsonEdge.append(edge.second);
          jsonEdges.append(jsonEdge);
     }

     root["nodes"] = jsonNodes;
     root["edges"] = jsonEdges;

     std::ofstream file(this->graphExportFilename, std::ofstream::out);
     if (!file.is_open())
     {
          throw std::runtime_error("Failed to open file for writing: " + graphExportFilename);
     }

     Json::StreamWriterBuilder writer;
     std::unique_ptr<Json::StreamWriter> jsonWriter(writer.newStreamWriter());
     jsonWriter->write(root, &file);
     file.close();
}