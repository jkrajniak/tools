/*
 *            Copyright 2009-2020 The VOTCA Development Team
 *                       (http://www.votca.org)
 *
 *      Licensed under the Apache License, Version 2.0 (the "License")
 *
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef VOTCA_TOOLS_GRAPH_DF_VISITOR_H
#define VOTCA_TOOLS_GRAPH_DF_VISITOR_H

// Standard includes
#include <list>

// Local VOTCA includes
#include "graphvisitor.h"

/**
 * \brief A breadth first (DF) graph visitor
 *
 * This graph visitor will explore the vertices closest to the starting node
 * first and proceed outwards.
 *
 */
namespace votca {
namespace tools {

class Graph;
class Edge;
class GraphNode;

class Graph_DF_Visitor : public GraphVisitor {
 private:
  std::list<Edge> edge_list_;

  /// The core of the breadth first visitor is in how the edges are added
  /// to the queue in this function
  void addEdges_(const Graph& g, Index vertex) override;
  Edge getEdge_() override;

 public:
  Graph_DF_Visitor() = default;
  bool queEmpty() const override;
};
}  // namespace tools
}  // namespace votca
#endif  // VOTCA_TOOLS_GRAPH_DF_VISITOR_H
