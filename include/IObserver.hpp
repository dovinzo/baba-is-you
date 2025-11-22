#ifndef IOBSERVER_HPP
#define IOBSERVER_HPP

#include "IReadOnlyModel.hpp"

class IObserver
{
    public:
        virtual ~IObserver() = default;
        virtual void update() = 0;
};

#endif