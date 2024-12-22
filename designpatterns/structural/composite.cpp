//
//  composite.cpp
//  designpatterns
//
//  Created by Ashish Jambhulkar on 12/22/24.
//

//The Composite Design Pattern is a structural design pattern that lets you treat individual objects and compositions of objects uniformly. It is particularly useful for representing part-whole hierarchies, such as trees.
//
//Intuitive Analogy
//Imagine a company structure:
//
//The CEO oversees multiple managers.
//Each manager supervises a team of employees.
//Each employee can perform tasks, and so can managers and the CEO.
//You want to be able to:
//
//Treat individual employees and groups of employees (like managers or the CEO) in the same way.
//Perform operations like assigning tasks to the entire hierarchy without worrying whether you're dealing with an individual or a group.
//This is where the Composite Pattern shines:
//
//Leaf nodes: Employees (individual objects).
//Composite nodes: Managers and the CEO (objects that group other objects).
//Components of the Composite Pattern
//Component:
//The common interface for both leaf nodes and composites.
//Leaf:
//Represents individual objects in the hierarchy.
//Composite:
//Represents groups of objects that can contain leaves or other composites.

#include <iostream>
#include <vector>
#include <memory>
#include <string>

// Component Interface
class Employee {
public:
    virtual void showDetails() const = 0; // Common operation for both leaves and composites
    virtual ~Employee() = default;
};

class Developer : public Employee {
private:
    std::string name;
    std::string position;

public:
    Developer(const std::string& name, const std::string& position)
        : name(name), position(position) {}

    void showDetails() const override {
        std::cout << "Developer: " << name << ", Position: " << position << std::endl;
    }
};

class Designer : public Employee {
private:
    std::string name;
    std::string position;

public:
    Designer(const std::string& name, const std::string& position)
        : name(name), position(position) {}

    void showDetails() const override {
        std::cout << "Designer: " << name << ", Position: " << position << std::endl;
    }
};


class Manager : public Employee {
private:
    std::string name;
    std::vector<std::shared_ptr<Employee>> team; // Can hold other Employees (leaves or composites)

public:
    explicit Manager(const std::string& name) : name(name) {}

    void addEmployee(const std::shared_ptr<Employee>& employee) {
        team.push_back(employee);
    }

    void showDetails() const override {
        std::cout << "Manager: " << name << "\n";
        for (const auto& employee : team) {
            employee->showDetails();
        }
    }
};

int main() {
    // Create leaf nodes
    auto dev1 = std::make_shared<Developer>("Alice", "Frontend Developer");
    auto dev2 = std::make_shared<Developer>("Bob", "Backend Developer");
    auto designer = std::make_shared<Designer>("Charlie", "UX Designer");

    // Create composite nodes
    auto teamLead = std::make_shared<Manager>("Team Lead");
    teamLead->addEmployee(dev1);
    teamLead->addEmployee(dev2);
    teamLead->addEmployee(designer);

    auto generalManager = std::make_shared<Manager>("General Manager");
    generalManager->addEmployee(teamLead);

    // Show details of the entire hierarchy
    generalManager->showDetails();

    return 0;
}


//Manager: General Manager
//Manager: Team Lead
//Developer: Alice, Position: Frontend Developer
//Developer: Bob, Position: Backend Developer
//Designer: Charlie, Position: UX Designer


//Key Features of the Composite Pattern
//Uniformity:
//Treat leaves (individual objects) and composites (groups of objects) uniformly.
//Hierarchy Representation:
//Easily model tree-like structures such as organizational hierarchies or file systems.
//Scalability:
//Supports dynamic addition or removal of components.
//Real-World Applications
//UI Components:
//Buttons, text fields, and containers can all be treated as components in a graphical user interface.
//File Systems:
//Files (leaves) and directories (composites) in a file system hierarchy.
//Game Development:
//Game objects with individual components and groups of components, such as players and teams.
//Caveats
//Overhead:
//Introducing composite structures can add complexity, especially if the hierarchy is not needed.
//Type Safety:
//Treating leaves and composites uniformly may require type checks or downcasting in some cases.
