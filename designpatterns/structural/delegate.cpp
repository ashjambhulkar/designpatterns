//
//  delegate.cpp
//  designpatterns
//
//  Created by Ashish Jambhulkar on 12/22/24.
//

//The Delegate Design Pattern is not an official Gang of Four design pattern but is widely used in software development. It refers to a design approach where an object delegates responsibility for a specific task to another object, rather than handling the task itself. This pattern is particularly useful in scenarios where one object needs to achieve functionality but wants to keep the implementation flexible or reusable.
//
//Intuitive Analogy
//Imagine you're organizing a conference, and instead of handling all the tasks yourself (e.g., arranging catering, booking venues, inviting speakers), you delegate specific tasks to specialists:
//
//A caterer manages the food.
//An event planner books the venue.
//A PR agency handles invites.
//In programming terms:
//
//You are the delegator (the object delegating tasks).
//Specialists are delegates (objects that perform specific tasks).
//Key Characteristics of the Delegate Pattern
//Decoupling: Delegation allows the delegator to focus on high-level tasks and leave implementation details to other classes.
//Flexibility: You can easily swap out the delegate to change the behavior without modifying the delegator.
//Single Responsibility: The delegator doesn't need to handle every task directly, promoting cleaner, modular design.


#include <iostream>
#include <memory>

// Delegate Interface
class PrintStrategy {
public:
    virtual void print(const std::string& text) = 0;
    virtual ~PrintStrategy() = default;
};


class ConsolePrint : public PrintStrategy {
public:
    void print(const std::string& text) override {
        std::cout << "Printing to console: " << text << std::endl;
    }
};

class FilePrint : public PrintStrategy {
public:
    void print(const std::string& text) override {
        std::cout << "Saving to file: " << text << std::endl;
        // In a real implementation, you'd write to a file.
    }
};

class Printer {
private:
    std::shared_ptr<PrintStrategy> strategy; // Reference to a delegate

public:
    void setPrintStrategy(const std::shared_ptr<PrintStrategy>& newStrategy) {
        strategy = newStrategy;
    }

    void print(const std::string& text) {
        if (strategy) {
            strategy->print(text); // Delegate the task
        } else {
            std::cout << "No print strategy set!" << std::endl;
        }
    }
};

int main() {
    // Create the delegator
    Printer printer;

    // Create concrete delegates
    auto consolePrinter = std::make_shared<ConsolePrint>();
    auto filePrinter = std::make_shared<FilePrint>();

    // Set delegate to console printing and use it
    printer.setPrintStrategy(consolePrinter);
    printer.print("Hello, Console!");

    // Change delegate to file printing and use it
    printer.setPrintStrategy(filePrinter);
    printer.print("Hello, File!");

    return 0;
}

//Printing to console: Hello, Console!
//Saving to file: Hello, File!

//Key Benefits of the Delegate Pattern
//Decoupling:
//The delegator doesn't need to know the details of how tasks are performed.
//Makes it easier to modify or replace functionality.
//Flexibility:
//You can change behavior dynamically by swapping delegates.
//Reusability:
//Delegates can be reused in different contexts.
//Real-World Applications
//UI Frameworks:
//Event handling systems where UI components delegate events like button clicks to handler objects.
//Printing Services:
//Document printing where different strategies are used for printers, PDFs, or emails.
//Task Management:
//Applications that delegate tasks like file uploads or data processing to worker threads.
//Caveats
//Overhead:
//Indirection introduced by delegation might add slight performance overhead.
//Complexity:
//Managing many delegates and ensuring proper delegation can make code harder to follow.
