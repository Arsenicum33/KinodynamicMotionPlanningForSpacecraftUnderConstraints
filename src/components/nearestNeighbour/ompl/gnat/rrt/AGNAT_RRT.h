//
// Created by arseniy on 11.5.25.
//

#ifndef AGNAT_RRT_H
#define AGNAT_RRT_H
#include <components/solvers/RRT/treeUtils/TreeNode.h>

#include "components/nearestNeighbour/ompl/gnat/AGNATsearch.h"

template <typename  StoredType, typename SearchedType>
class AGNAT_RRT : public AGNATsearch<TreeNode<StoredType>, SearchedType> {};

#endif //AGNAT_RRT_H
