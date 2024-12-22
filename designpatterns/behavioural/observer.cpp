//
//  observer.cpp
//  designpatterns
//
//  Created by Ashish Jambhulkar on 12/22/24.
//

//The Observer Design Pattern is a behavioral design pattern used to create a one-to-many dependency between objects. When the state of one object (the subject) changes, all its dependent objects (the observers) are notified and updated automatically.
//
//Intuitive Analogy
//Think of a news agency and its subscribers:
//
//The news agency is the subject: It generates news updates.
//The subscribers are the observers: They are notified whenever there’s a new piece of news.
//If a new subscriber signs up, they start receiving updates. If an old subscriber unsubscribes, they stop getting updates. The news agency doesn’t need to know who the subscribers are; it simply broadcasts the updates.
//
//Components of the Observer Pattern
//Subject:
//Maintains a list of observers.
//Provides methods for adding, removing, and notifying observers.
//Observer:
//Defines an interface for objects that should be notified of changes in the subject.
//Concrete Subject:
//The actual subject that maintains the state and notifies observers of changes.
//Concrete Observers:
//Implement the observer interface and update their state when notified by the subject.


#include <iostream>
#include <vector>
#include <string>

// Observer Interface
class Observer {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Observer() = default;
};

class Subject {
public:
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify() = 0;
    virtual ~Subject() = default;
};


class NewsAgency : public Subject {
private:
    std::vector<Observer*> observers; // List of observers
    std::string latestNews;           // Subject state

public:
    void attach(Observer* observer) override {
        observers.push_back(observer);
    }

    void detach(Observer* observer) override {
        observers.erase(
            std::remove(observers.begin(), observers.end(), observer),
            observers.end());
    }

    void notify() override {
        for (Observer* observer : observers) {
            observer->update(latestNews);
        }
    }

    void setNews(const std::string& news) {
        latestNews = news;
        notify(); // Notify observers of the change
    }
};


class Subscriber : public Observer {
private:
    std::string name;

public:
    explicit Subscriber(const std::string& name) : name(name) {}

    void update(const std::string& message) override {
        std::cout << name << " received update: " << message << std::endl;
    }
};

int main() {
    // Create the subject
    NewsAgency agency;

    // Create observers
    Subscriber alice("Alice");
    Subscriber bob("Bob");
    Subscriber charlie("Charlie");

    // Attach observers to the subject
    agency.attach(&alice);
    agency.attach(&bob);

    // Change the subject's state and notify observers
    agency.setNews("Breaking News: Observer Pattern Implemented!");

    // Detach an observer
    agency.detach(&bob);

    // Change the subject's state again
    agency.setNews("Update: Observer Pattern is Awesome!");

    return 0;
}


//Alice received update: Breaking News: Observer Pattern Implemented!
//Bob received update: Breaking News: Observer Pattern Implemented!
//Alice received update: Update: Observer Pattern is Awesome!

//
//Key Features of the Observer Pattern
//Loose Coupling:
//The subject and observers are loosely coupled; the subject doesn’t need to know the concrete details of the observers.
//Dynamic Relationships:
//Observers can be added or removed at runtime.
//Scalability:
//Supports one-to-many relationships between objects.
//Real-World Applications
//Event Systems: GUIs where button clicks notify listeners.
//Publish-Subscribe Models: News feeds, email alerts, or stock market updates.
//Data Binding: Synchronizing UI elements with underlying data.
//Caveats
//Performance:
//Notifying a large number of observers can be slow.
//Unintended Dependencies:
//Observers must handle updates carefully to avoid inconsistencies or infinite loops.
