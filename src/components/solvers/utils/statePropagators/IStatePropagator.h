// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef ISTATEPROPAGATOR_H
#define ISTATEPROPAGATOR_H


template <typename PositionType>
class IStatePropagator : public IComponent
{
public:
    virtual PositionType propagate(const PositionType& current) = 0;
};



#endif //ISTATEPROPAGATOR_H
