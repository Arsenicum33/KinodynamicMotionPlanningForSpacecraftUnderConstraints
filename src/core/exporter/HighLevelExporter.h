//
// Created by arseniy on 13.1.25.
//

#ifndef HIGHLEVELEXPORTER_H
#define HIGHLEVELEXPORTER_H
#include <unordered_set>

#include "IHighLevelExporter.h"
#include "components/solvers/RRT/treeUtils/ANode.h"

struct Edge
{
    int first;
    int second;
};

inline bool operator==(Edge const& a, Edge const& b) noexcept {
    return a.first == b.first && a.second == b.second;
}

struct EdgeHash {
    size_t operator()(Edge const& e) const noexcept {
        return (static_cast<size_t>(e.first) << 32)
             ^  static_cast<size_t>(e.second);
    }
};


class HighLevelExporter : public IHighLevelExporter
{
public:
    HighLevelExporter(bool exportSolution = false) : exportSolution(exportSolution) {};
    void exportOutput(IComponentManager* componentManager,ExecutorOutput executorOutput) override;
private:
    bool exportSolution = false;
    std::string graphExportFilename = "graph.json";
    std::unordered_set<Edge, EdgeHash> getSolverTreeEdges( std::vector<std::shared_ptr<ANode>>);
    void exportSolutionGraph(std::vector<std::shared_ptr<ANode>>& nodes, std::unordered_set<Edge, EdgeHash>& edges);
};



#endif //HIGHLEVELEXPORTER_H
