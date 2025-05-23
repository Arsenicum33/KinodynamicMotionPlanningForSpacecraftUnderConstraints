// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


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
