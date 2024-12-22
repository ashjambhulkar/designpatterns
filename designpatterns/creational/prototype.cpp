//
//  prototype.cpp
//  designpatterns
//
//  Created by Ashish Jambhulkar on 12/22/24.
//

//The Prototype Design Pattern is a creational design pattern that allows you to create new objects by copying (cloning) an existing object (the prototype). It provides a mechanism to avoid creating objects from scratch when the cost of object creation is expensive.
//
//Intuitive Analogy
//Imagine you're a painter, and you need multiple copies of the same stencil for a project. Instead of redrawing the stencil every time (which is slow and error-prone), you create one master stencil (the prototype) and duplicate it for reuse.
//
//In programming:
//
//The master stencil is the prototype.
//Cloning creates new objects based on this prototype.
//Key Components of the Prototype Pattern
//Prototype Interface:
//Defines a method (clone()) for creating a copy of the object.
//Concrete Prototype:
//Implements the clone() method and provides the actual cloning logic.
//Client:
//Creates new objects by cloning the prototype.
//Why Use the Prototype Pattern?
//Avoid Expensive Creation:
//Reuse an existing object as a template instead of recreating it from scratch.
//Runtime Flexibility:
//Create objects dynamically at runtime without hardcoding their classes.


#include <iostream>
#include <memory>

// Prototype Interface
class Shape {
public:
    virtual std::shared_ptr<Shape> clone() const = 0; // Clone method
    virtual void draw() const = 0;                   // Example operation
    virtual ~Shape() = default;
};

class Circle : public Shape {
private:
    int radius;

public:
    Circle(int r) : radius(r) {}

    // Copy constructor
    Circle(const Circle& other) : radius(other.radius) {}

    std::shared_ptr<Shape> clone() const override {
        return std::make_shared<Circle>(*this); // Create a copy of the object
    }

    void draw() const override {
        std::cout << "Drawing a Circle with radius " << radius << "\n";
    }
};

class Rectangle : public Shape {
private:
    int width, height;

public:
    Rectangle(int w, int h) : width(w), height(h) {}

    // Copy constructor
    Rectangle(const Rectangle& other) : width(other.width), height(other.height) {}

    std::shared_ptr<Shape> clone() const override {
        return std::make_shared<Rectangle>(*this); // Create a copy of the object
    }

    void draw() const override {
        std::cout << "Drawing a Rectangle with width " << width << " and height " << height << "\n";
    }
};

int main() {
    // Create prototypes
    std::shared_ptr<Shape> circlePrototype = std::make_shared<Circle>(10);
    std::shared_ptr<Shape> rectanglePrototype = std::make_shared<Rectangle>(5, 8);

    // Clone and use the circle
    std::shared_ptr<Shape> clonedCircle = circlePrototype->clone();
    clonedCircle->draw(); // Output: Drawing a Circle with radius 10

    // Clone and use the rectangle
    std::shared_ptr<Shape> clonedRectangle = rectanglePrototype->clone();
    clonedRectangle->draw(); // Output: Drawing a Rectangle with width 5 and height 8

    return 0;
}


//Key Features of the Prototype Pattern
//Cloning Flexibility:
//Clients don’t need to know the exact class of the object; they just call clone().
//Reduced Initialization Costs:
//Copying an existing object is often faster than initializing one from scratch.
//Runtime Object Configuration:
//Allows dynamic creation of objects without hardcoding classes.
//Real-World Applications
//Game Development:
//Clone objects like enemies, bullets, or game characters to avoid repetitive initialization.
//Document Templates:
//Use a prototype for creating documents with predefined formats.
//GUI Elements:
//Clone widgets with specific properties (e.g., buttons, text boxes).
//Caveats
//Deep vs. Shallow Copy:
//Ensure that the clone() method creates a deep copy if the object contains pointers or references to other objects.
//Overhead:
//Managing the clone() method can add complexity, especially when dealing with inheritance hierarchies.
//Deep vs. Shallow Copy Example
//Shallow Copy: Copies the object's structure but not the objects it references (pointers point to the same memory).
//Deep Copy: Copies both the object and any objects it references, ensuring independence.
//For deep copies, ensure all dynamically allocated members are cloned in the clone() method.
