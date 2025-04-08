//
// Created by arseniy on 7.4.25.
//

#ifndef ISTATEPROPAGATOR_H
#define ISTATEPROPAGATOR_H


template <typename PositionType>
class IStatePropagator : public IComponent
{
public:
    virtual PositionType propagate(const PositionType& current) = 0;
};



#endif //ISTATEPROPAGATOR_H
