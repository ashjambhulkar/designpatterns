//
//  builder.cpp
//  designpatterns
//
//  Created by Ashish Jambhulkar on 12/22/24.
//


//
//The Builder Design Pattern is a creational design pattern used to construct complex objects step by step. It separates the construction process from the final representation, allowing the same construction process to create different representations.
//
//Intuitive Analogy
//Imagine you are building a custom pizza. A pizza order can vary widely:
//
//Crust type (thin, thick, gluten-free)
//Toppings (pepperoni, mushrooms, olives, etc.)
//Sauce type (marinara, pesto, alfredo)
//If you were to make all these combinations in a single class, it would get overwhelming. Instead, you employ a pizza builder. The builder takes care of adding crust, sauce, and toppings in a specific sequence.
//
//The same process can now create different pizzas:
//
//A vegetarian pizza by adding veggies.
//A meat-lovers pizza by adding meats.
//The Builder Pattern lets you create complex objects (like pizzas) in a controlled, step-by-step way.
//
//Technical Explanation
//Key Components of the Builder Pattern
//
//Builder: Abstract interface for building the product step by step.
//Concrete Builder: Implements the builder interface and provides specific steps for building the product.
//Director: Controls the sequence of the construction process.
//Product: The final object being built.
#include <iostream>

using namespace std;

class Pizza {
public:
    std::string crust;
    std::string sauce;
    std::vector<std::string> toppings;

    void showPizza() {
        std::cout << "Pizza with " << crust << " crust, " << sauce << " sauce, and toppings: ";
        for (const auto& topping : toppings) {
            std::cout << topping << " ";
        }
        std::cout << std::endl;
    }
};


class PizzaBuilder {
public:
    virtual void setCrust() = 0;
    virtual void setSauce() = 0;
    virtual void addToppings() = 0;
    virtual Pizza* getPizza() = 0;
};


class VeggiePizzaBuilder : public PizzaBuilder {
private:
    Pizza* pizza;

public:
    VeggiePizzaBuilder() {
        pizza = new Pizza();
    }

    void setCrust() override {
        pizza->crust = "Thin";
    }

    void setSauce() override {
        pizza->sauce = "Tomato";
    }

    void addToppings() override {
        pizza->toppings = {"Bell Peppers", "Mushrooms", "Olives"};
    }

    Pizza* getPizza() override {
        return pizza;
    }
};

class MeatLoversPizzaBuilder : public PizzaBuilder {
private:
    Pizza* pizza;

public:
    MeatLoversPizzaBuilder() {
        pizza = new Pizza();
    }

    void setCrust() override {
        pizza->crust = "Thick";
    }

    void setSauce() override {
        pizza->sauce = "Barbecue";
    }

    void addToppings() override {
        pizza->toppings = {"Pepperoni", "Sausage", "Bacon"};
    }

    Pizza* getPizza() override {
        return pizza;
    }
};


class PizzaDirector {
public:
    void constructPizza(PizzaBuilder* builder) {
        builder->setCrust();
        builder->setSauce();
        builder->addToppings();
    }
};


int main() {
    // Create builders
    VeggiePizzaBuilder veggieBuilder;
    MeatLoversPizzaBuilder meatLoversBuilder;

    // Create director
    PizzaDirector director;

    // Construct and display a veggie pizza
    director.constructPizza(&veggieBuilder);
    Pizza* veggiePizza = veggieBuilder.getPizza();
    veggiePizza->showPizza();

    // Construct and display a meat-lovers pizza
    director.constructPizza(&meatLoversBuilder);
    Pizza* meatPizza = meatLoversBuilder.getPizza();
    meatPizza->showPizza();

    // Clean up
    delete veggiePizza;
    delete meatPizza;

    return 0;
}

//
//Key Benefits
//Step-by-Step Construction: Allows you to create complex objects incrementally.
//Reusability: The same builder can construct different representations (e.g., veggie or meat pizza).
//Flexibility: The construction process can vary without changing the final product.
//Caveats
//Overhead: If the product is simple, the Builder Pattern might be overkill.
//Coupling: Adding new types of products may require changes to the builder and director.
