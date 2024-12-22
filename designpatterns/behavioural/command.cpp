//
//  command.cpp
//  designpatterns
//
//  Created by Ashish Jambhulkar on 12/22/24.
//

//The Command Design Pattern is a behavioral design pattern that encapsulates a request as an object, allowing you to parameterize objects with operations, delay execution, or queue requests. It is particularly useful for implementing undo/redo functionality, transaction management, and event handling systems.
//
//Intuitive Analogy
//Imagine a universal remote control for a home theater system. The remote has buttons like "Play," "Pause," "Volume Up," and "Volume Down." Each button represents a command, but the remote doesn’t directly execute the command. Instead:
//
//Pressing a button sends a command to the device (TV, DVD player, etc.).
//The device interprets and executes the command.
//This separation allows you to:
//
//Assign different actions to buttons (flexibility).
//Save a history of commands for undo/redo functionality.
//In programming, the Command Pattern works like this:
//
//Invoker: The remote control (triggers commands).
//Command: The button press (encapsulates the request).
//Receiver: The TV or DVD player (executes the request).
//Components of the Command Pattern
//Command Interface: Defines the method that all concrete commands implement.
//Concrete Commands: Implement the command interface and define the specific action for the receiver.
//Invoker: Triggers commands by calling their methods.
//Receiver: Performs the actual work when a command is executed.

#include <iostream>
#include <memory>

// Command Interface
class Command {
public:
    virtual void execute() = 0;  // Execute the command
    virtual void undo() = 0;     // Undo the command
    virtual ~Command() = default;
};

class Light {
public:
    void turnOn() {
        std::cout << "Light is ON\n";
    }

    void turnOff() {
        std::cout << "Light is OFF\n";
    }
};

class LightOnCommand : public Command {
private:
    Light* light; // Receiver

public:
    explicit LightOnCommand(Light* light) : light(light) {}

    void execute() override {
        light->turnOn();
    }

    void undo() override {
        light->turnOff();
    }
};

class LightOffCommand : public Command {
private:
    Light* light; // Receiver

public:
    explicit LightOffCommand(Light* light) : light(light) {}

    void execute() override {
        light->turnOff();
    }

    void undo() override {
        light->turnOn();
    }
};

class RemoteControl {
private:
    std::shared_ptr<Command> command;

public:
    void setCommand(std::shared_ptr<Command> cmd) {
        command = cmd;
    }

    void pressButton() {
        if (command) {
            command->execute();
        }
    }

    void pressUndo() {
        if (command) {
            command->undo();
        }
    }
};

int main() {
    // Create the receiver
    Light livingRoomLight;

    // Create commands
    auto lightOn = std::make_shared<LightOnCommand>(&livingRoomLight);
    auto lightOff = std::make_shared<LightOffCommand>(&livingRoomLight);

    // Create invoker
    RemoteControl remote;

    // Turn the light ON
    remote.setCommand(lightOn);
    remote.pressButton(); // Output: Light is ON

    // Undo the command (turn the light OFF)
    remote.pressUndo();   // Output: Light is OFF

    // Turn the light OFF
    remote.setCommand(lightOff);
    remote.pressButton(); // Output: Light is OFF

    // Undo the command (turn the light ON)
    remote.pressUndo();   // Output: Light is ON

    return 0;
}

//Key Features of the Command Pattern
//Encapsulation: Commands encapsulate a request as an object, separating the invoker from the receiver.
//Flexibility: Allows you to queue, log, or undo/redo commands.
//Open/Closed Principle: Adding new commands doesn’t require modifying the invoker or receiver.
//Real-World Applications
//Undo/Redo Functionality: Applications like text editors or image processors use the Command Pattern to manage undoable operations.
//Task Scheduling: Queuing operations for execution later (e.g., in games or job processing).
//Macro Recording: Recording sequences of commands for automation.
//Caveats
//Complexity: Adding a command for every possible operation can lead to many classes.
//Overhead: Encapsulation adds additional layers, which might be overkill for simple use cases.
