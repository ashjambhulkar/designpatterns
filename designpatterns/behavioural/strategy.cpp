//
//  strategy.cpp
//  designpatterns
//
//  Created by Ashish Jambhulkar on 12/22/24.
//

//The Strategy Design Pattern is a behavioral design pattern that defines a family of algorithms, encapsulates each one, and makes them interchangeable. It lets the algorithm vary independently from the clients that use it.
//
//Intuitive Analogy
//Imagine you're navigating a city using a GPS. The GPS can calculate routes using different strategies:
//
//Shortest Route: Optimize for the shortest distance.
//Fastest Route: Optimize for the least travel time.
//Scenic Route: Optimize for the most enjoyable views.
//The Strategy Pattern allows you to switch between these algorithms without changing the GPS's core functionality. The GPS itself doesn't need to know how each route is calculated—each route calculation strategy is encapsulated separately.
//
//Components of the Strategy Pattern
//Context:
//The class that uses a strategy object. It delegates algorithm execution to the strategy.
//Strategy Interface:
//Defines a common interface for all supported algorithms.
//Concrete Strategies:
//Implement different variations of the algorithm.


#include <iostream>
#include <memory>

// Strategy Interface
class RouteStrategy {
public:
    virtual void calculateRoute() const = 0;
    virtual ~RouteStrategy() = default;
};

class ShortestRoute : public RouteStrategy {
public:
    void calculateRoute() const override {
        std::cout << "Calculating the shortest route.\n";
    }
};

class FastestRoute : public RouteStrategy {
public:
    void calculateRoute() const override {
        std::cout << "Calculating the fastest route.\n";
    }
};

class ScenicRoute : public RouteStrategy {
public:
    void calculateRoute() const override {
        std::cout << "Calculating the scenic route.\n";
    }
};

class GPSNavigator {
private:
    std::shared_ptr<RouteStrategy> strategy; // Strategy object

public:
    void setStrategy(const std::shared_ptr<RouteStrategy>& newStrategy) {
        strategy = newStrategy;
    }

    void navigate() const {
        if (strategy) {
            strategy->calculateRoute();
        } else {
            std::cout << "No strategy set.\n";
        }
    }
};

int main() {
    // Create the context
    GPSNavigator navigator;

    // Create different strategies
    auto shortestRoute = std::make_shared<ShortestRoute>();
    auto fastestRoute = std::make_shared<FastestRoute>();
    auto scenicRoute = std::make_shared<ScenicRoute>();

    // Use the shortest route strategy
    navigator.setStrategy(shortestRoute);
    navigator.navigate(); // Output: Calculating the shortest route.

    // Switch to the fastest route strategy
    navigator.setStrategy(fastestRoute);
    navigator.navigate(); // Output: Calculating the fastest route.

    // Switch to the scenic route strategy
    navigator.setStrategy(scenicRoute);
    navigator.navigate(); // Output: Calculating the scenic route.

    return 0;
}

//
//Key Features of the Strategy Pattern
//Encapsulation of Algorithms:
//Each algorithm is in its own class, making it easier to modify or add new strategies.
//Interchangeability:
//Strategies can be swapped at runtime without changing the client.
//Open/Closed Principle:
//New algorithms can be added without modifying the existing code.
//Real-World Applications
//Sorting Algorithms:
//Implement different sorting strategies like quicksort, mergesort, or bubblesort.
//Payment Methods:
//Switch between payment options like credit card, PayPal, or cryptocurrency.
//AI Behaviors:
//Different strategies for decision-making in games or robotics.
//Caveats
//Overhead:
//Introducing a strategy interface and multiple classes for each algorithm can add complexity.
//Code Coupling:
//The context needs to know which strategy to use, which may lead to tight coupling if not managed carefully.
