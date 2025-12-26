#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include <vector>
#include "Notification.hpp"
#include "Observer.hpp"

class Subject
{
    public:
        virtual ~Subject() = default;
        void addObserver(Observer* observer);
        void removeObserver(Observer* observer);
    protected:
        void notifyObservers(const Notification& notification);
    private:
        std::vector<Observer*> observers;
};

#endif
