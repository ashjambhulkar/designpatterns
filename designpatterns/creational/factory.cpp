//
//  factory.cpp
//  designpatterns
//
//  Created by Ashish Jambhulkar on 12/22/24.
//

//The Factory Design Pattern is a creational design pattern that provides a way to create objects without specifying the exact class of the object being created. It delegates the responsibility of instantiating objects to subclasses or a dedicated factory class, making your code more flexible and scalable.
//
//Intuitive Analogy
//Imagine you own a car dealership. Customers come in and ask for different types of cars: sedans, SUVs, or sports cars. Instead of building each car manually, you use a car factory:
//
//The factory knows how to create all types of cars.
//The customer simply specifies what type of car they want, and the factory produces it.
//This abstraction ensures that:
//
//The customer doesn’t need to know how each car is built.
//Adding a new car type (e.g., electric cars) requires updating only the factory, not the customer interaction.
//Technical Explanation
//The Factory Pattern focuses on:
//
//Encapsulation of Object Creation: The exact creation process is hidden from the client.
//Flexibility: Makes it easy to add new types of objects without modifying existing code.
//Types of Factory Patterns
//There are two common variations:
//
//Simple Factory: A static method is used to create objects. Not a true design pattern, but a helpful concept.
//Factory Method: A method is defined in an interface or abstract class and implemented by subclasses to create objects.
//Implementation in C++
//Here’s how you can implement the Factory Pattern in C++.
//
//1. Simple Factory Pattern
//
//This approach uses a single method to create objects based on input.

#include <iostream>
#include <memory>

// Product Interface
class Car {
public:
    virtual void drive() const = 0;
    virtual ~Car() {}
};

// Concrete Products
class Sedan : public Car {
public:
    void drive() const override {
        std::cout << "Driving a Sedan.\n";
    }
};

class SUV : public Car {
public:
    void drive() const override {
        std::cout << "Driving an SUV.\n";
    }
};

class SportsCar : public Car {
public:
    void drive() const override {
        std::cout << "Driving a Sports Car.\n";
    }
};

// Factory Class
class CarFactory {
public:
    static std::unique_ptr<Car> createCar(const std::string& type) {
        if (type == "Sedan") {
            return std::make_unique<Sedan>();
        } else if (type == "SUV") {
            return std::make_unique<SUV>();
        } else if (type == "SportsCar") {
            return std::make_unique<SportsCar>();
        } else {
            throw std::invalid_argument("Unknown car type");
        }
    }
};

int main() {
    // Create cars using the factory
    auto sedan = CarFactory::createCar("Sedan");
    auto suv = CarFactory::createCar("SUV");

    sedan->drive();  // Output: Driving a Sedan.
    suv->drive();    // Output: Driving an SUV.

    return 0;
}
//2. Factory Method Pattern
//
//In this variation, the object creation is delegated to subclasses.

#include <iostream>
#include <memory>

// Product Interface
class Car {
public:
    virtual void drive() const = 0;
    virtual ~Car() {}
};

// Concrete Products
class Sedan : public Car {
public:
    void drive() const override {
        std::cout << "Driving a Sedan.\n";
    }
};

class SUV : public Car {
public:
    void drive() const override {
        std::cout << "Driving an SUV.\n";
    }
};

// Creator Interface
class CarFactory {
public:
    virtual std::unique_ptr<Car> createCar() const = 0;
    virtual ~CarFactory() {}
};

// Concrete Factories
class SedanFactory : public CarFactory {
public:
    std::unique_ptr<Car> createCar() const override {
        return std::make_unique<Sedan>();
    }
};

class SUVFactory : public CarFactory {
public:
    std::unique_ptr<Car> createCar() const override {
        return std::make_unique<SUV>();
    }
};

int main() {
    // Use specific factories to create cars
    SedanFactory sedanFactory;
    SUVFactory suvFactory;

    auto sedan = sedanFactory.createCar();
    auto suv = suvFactory.createCar();

    sedan->drive();  // Output: Driving a Sedan.
    suv->drive();    // Output: Driving an SUV.

    return 0;
}
//Differences Between Simple Factory and Factory Method
//Aspect    Simple Factory    Factory Method
//Implementation    Single static method in a class.    Subclasses define how to create objects.
//Extensibility    Harder to add new product types.    Easier to extend by adding new factories.
//Flexibility    Centralized object creation.    Decentralized, customizable creation logic.
//Key Benefits
//Encapsulation: Hides the details of object creation.
//Scalability: Easy to introduce new products without changing client code.
//Single Responsibility: Factory classes handle object creation, leaving clients focused on their tasks.
//Disadvantages
//Complexity: Adds extra classes and abstraction layers.
//Overhead: May be overkill for simple applications.
