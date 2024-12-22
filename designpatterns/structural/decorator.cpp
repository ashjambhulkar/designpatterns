//
//  decorator.cpp
//  designpatterns
//
//  Created by Ashish Jambhulkar on 12/22/24.
//

//The Decorator Design Pattern is a structural design pattern that allows you to dynamically add new behaviors or responsibilities to objects without modifying their code.
//
//Intuitive Analogy
//Think about a plain vanilla ice cream. By itself, it’s simple and tasty. But maybe you want chocolate syrup, nuts, or sprinkles on top. Instead of changing the recipe for vanilla ice cream (modifying its class), you can decorate it by layering these extras on top.
//
//In programming terms:
//
//The vanilla ice cream is your base class (core functionality).
//Each topping is a decorator that wraps the base class and adds functionality.
//Key Components of the Decorator Pattern
//Component: The base interface or abstract class defining the common behavior.
//Concrete Component: The core class that we decorate (e.g., vanilla ice cream).
//Decorator: An abstract class that implements the component interface and wraps the component.
//Concrete Decorators: Add specific behaviors by extending the decorator class.


#include <iostream>
#include <memory>

// Base Component
class Coffee {
public:
    virtual std::string getDescription() const = 0;
    virtual double getCost() const = 0;
    virtual ~Coffee() = default;
};


class PlainCoffee : public Coffee {
public:
    std::string getDescription() const override {
        return "Plain Coffee";
    }

    double getCost() const override {
        return 2.0; // Base price of plain coffee
    }
};


class CoffeeDecorator : public Coffee {
protected:
    std::shared_ptr<Coffee> coffee; // Composition: wraps a Coffee object

public:
    CoffeeDecorator(std::shared_ptr<Coffee> coffee) : coffee(std::move(coffee)) {}

    std::string getDescription() const override {
        return coffee->getDescription();
    }

    double getCost() const override {
        return coffee->getCost();
    }
};

class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(std::shared_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {}

    std::string getDescription() const override {
        return coffee->getDescription() + ", Milk";
    }

    double getCost() const override {
        return coffee->getCost() + 0.5; // Add cost of milk
    }
};

class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(std::shared_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {}

    std::string getDescription() const override {
        return coffee->getDescription() + ", Sugar";
    }

    double getCost() const override {
        return coffee->getCost() + 0.2; // Add cost of sugar
    }
};

class CaramelDecorator : public CoffeeDecorator {
public:
    CaramelDecorator(std::shared_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {}

    std::string getDescription() const override {
        return coffee->getDescription() + ", Caramel";
    }

    double getCost() const override {
        return coffee->getCost() + 0.7; // Add cost of caramel
    }
};

int main() {
    // Start with plain coffee
    std::shared_ptr<Coffee> myCoffee = std::make_shared<PlainCoffee>();
    std::cout << myCoffee->getDescription() << " costs $" << myCoffee->getCost() << "\n";

    // Add milk
    myCoffee = std::make_shared<MilkDecorator>(myCoffee);
    std::cout << myCoffee->getDescription() << " costs $" << myCoffee->getCost() << "\n";

    // Add sugar
    myCoffee = std::make_shared<SugarDecorator>(myCoffee);
    std::cout << myCoffee->getDescription() << " costs $" << myCoffee->getCost() << "\n";

    // Add caramel
    myCoffee = std::make_shared<CaramelDecorator>(myCoffee);
    std::cout << myCoffee->getDescription() << " costs $" << myCoffee->getCost() << "\n";

    return 0;
}

//Plain Coffee costs $2
//Plain Coffee, Milk costs $2.5
//Plain Coffee, Milk, Sugar costs $2.7
//Plain Coffee, Milk, Sugar, Caramel costs $3.4


//Key Benefits
//Open/Closed Principle: You can extend an object’s functionality without modifying its structure.
//Flexibility: You can combine multiple decorators dynamically.
//Separation of Concerns: Each decorator focuses on a single behavior.
//Caveats
//Complexity: Too many decorators can make the code harder to understand.
//Overhead: Wrapping objects can introduce runtime overhead.
