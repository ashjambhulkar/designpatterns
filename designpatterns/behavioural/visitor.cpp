//
//  visitor.cpp
//  designpatterns
//
//  Created by Ashish Jambhulkar on 12/22/24.
//


//Intuitive Analogy
//Imagine you run a zoo. The zoo has many types of animals: lions, penguins, elephants, etc. You have two tasks:
//
//Feed each animal.
//Check their health.
//Now, each animal type eats differently and has unique health requirements. You could modify every animal's class to include feed and checkHealth methods. But what if next month you need a new task, like cleanEnclosure? This would require modifying all animal classes again, which is cumbersome and violates the Open/Closed Principle (classes should be open for extension but closed for modification).
//
//Instead, the Visitor Pattern allows you to create a zookeeper (a visitor) who knows how to perform tasks (operations) like feeding, health checking, and cleaning. The animals accept the zookeeper as a guest and let the zookeeper decide what to do. This way, you can extend operations (add new tasks) without changing the animals.

//Technical Explanation
//Key Concepts in the Visitor Pattern:
//
//Visitor: Defines operations to be performed on elements of the object structure.
//Element: Represents the object structure that accepts the visitor.
//Accept Method: Each element implements an accept(Visitor) method to let the visitor perform its operation.

#include <iostream>

using namespace std;
class AnimalVisitor {
public:
    virtual void visitLion(class Lion* lion) = 0;
    virtual void visitPenguin(class Penguin* penguin) = 0;
    virtual void visitElephant(class Elephant* elephant) = 0;
};

class Animal {
public:
    virtual void accept(AnimalVisitor* visitor) = 0; // Accepts a visitor
};

class Lion : public Animal {
public:
    void accept(AnimalVisitor* visitor) override {
        visitor->visitLion(this); // Let the visitor visit a Lion
    }
};

class Penguin : public Animal {
public:
    void accept(AnimalVisitor* visitor) override {
        visitor->visitPenguin(this); // Let the visitor visit a Penguin
    }
};

class Elephant : public Animal {
public:
    void accept(AnimalVisitor* visitor) override {
        visitor->visitElephant(this); // Let the visitor visit an Elephant
    }
};

class FeedingVisitor : public AnimalVisitor {
public:
    void visitLion(Lion* lion) override {
        std::cout << "Feeding the lion meat.\n";
    }
    void visitPenguin(Penguin* penguin) override {
        std::cout << "Feeding the penguin fish.\n";
    }
    void visitElephant(Elephant* elephant) override {
        std::cout << "Feeding the elephant bananas.\n";
    }
};

class HealthCheckVisitor : public AnimalVisitor {
public:
    void visitLion(Lion* lion) override {
        std::cout << "Checking the lion's teeth.\n";
    }
    void visitPenguin(Penguin* penguin) override {
        std::cout << "Checking the penguin's feathers.\n";
    }
    void visitElephant(Elephant* elephant) override {
        std::cout << "Checking the elephant's tusks.\n";
    }
};


int main() {
    // Create animals
    Lion lion;
    Penguin penguin;
    Elephant elephant;

    // Create visitors
    FeedingVisitor feedingVisitor;
    HealthCheckVisitor healthCheckVisitor;

    // Apply visitors to animals
    lion.accept(&feedingVisitor);
    penguin.accept(&feedingVisitor);
    elephant.accept(&feedingVisitor);

    lion.accept(&healthCheckVisitor);
    penguin.accept(&healthCheckVisitor);
    elephant.accept(&healthCheckVisitor);

    return 0;
}


//Key Benefits
//Extensibility: You can add new operations (visitors) without modifying the existing classes.
//Separation of Concerns: Keeps operations separate from the object structure.
//Caveats
//Double Dispatch: The pattern relies on double dispatch, meaning the operation depends on both the visitor type and the element type.
//Complexity: Adding a new type of element requires modifying the visitor interface and all concrete visitors.
