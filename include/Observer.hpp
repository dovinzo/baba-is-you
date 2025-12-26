#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <vector>
#include "Notification.hpp"

class Observer
{
    public:
        virtual ~Observer() = default;
        virtual void update(const Notification& notification) = 0;
};

#endif
