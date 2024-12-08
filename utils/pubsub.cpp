#include "pubsub.hpp"

void Publisher::notify(void *what)
{
    std::list<Subscriber *>::iterator p;
    for (p = subscribers.begin(); p != subscribers.end(); p++)
    {
        (*p)->update(this, what);
    }
}