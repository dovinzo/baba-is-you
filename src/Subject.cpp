#include "Observer.hpp"
#include "Subject.hpp"
#include "Notification.hpp"

void Subject::addObserver(Observer* observer)
{
    observers.push_back(observer);
}

void Subject::removeObserver(Observer* observer)
{
    for (int i = 0 ; i < static_cast<int>(observers.size()) ; i++)
    {
        if (observers[i] == observer)
        {
            observers.erase(observers.begin() + i);
            break;
        }
    }
}

void Subject::notifyObservers(const Notification& notification)
{
    for (int i = 0 ; i < static_cast<int>(observers.size()) ; i++)
    {
        observers[i]->update(notification);
    }
}
