//
// Created by arseniy on 28.10.24.
//

#ifndef IMPNNSEARCH_H
#define IMPNNSEARCH_H
#include <memory>

#include "components/IComponent.h"
#include "../INearestNeighborSearch.h"

template <typename StoredType, typename SearchedType>
class IMPNNsearch : public INearestNeighborSearch<StoredType, SearchedType>
{
};

#endif //IMPNNSEARCH_H
