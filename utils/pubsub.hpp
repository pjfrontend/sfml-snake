#pragma once

#include <list> // for our appStateSubscriber list

class Publisher; // forward reference

class Subscriber
{
public:
    virtual ~Subscriber() {}
    virtual void update(Publisher *who, void *what = 0) = 0;
};

class Publisher
{
public:
    Publisher() {}
    virtual ~Publisher() {}
    void subscribe(Subscriber *s) { subscribers.push_back(s); }
    void unsubscribe(Subscriber *s) { subscribers.remove(s); }
    void notify(void *what = 0);

private:
    std::list<Subscriber *> subscribers;
};
