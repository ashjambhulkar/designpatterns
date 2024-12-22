//
//  bridge.cpp
//  designpatterns
//
//  Created by Ashish Jambhulkar on 12/22/24.
//

//The Bridge Design Pattern is a structural design pattern that decouples an abstraction from its implementation, allowing the two to evolve independently. It achieves this by creating two separate class hierarchies: one for the abstraction and one for the implementation, and connects them using a "bridge."
//
//Intuitive Analogy
//Think about a remote control for a TV. The remote control (abstraction) is responsible for controlling the TV (implementation). Different types of remotes (basic remote, advanced remote) can control different types of TVs (LED, OLED, Smart TV). The bridge pattern allows the remote and the TV to evolve separately:
//
//A new type of remote can be created without changing the TV implementation.
//A new type of TV can be introduced without changing the remotes.
//Components of the Bridge Pattern
//Abstraction:
//Defines the high-level interface for the client.
//Maintains a reference to the implementation.
//Refined Abstraction:
//Extends the abstraction to add more operations.
//Implementor:
//Defines the interface for the implementation.
//Concrete Implementor:
//Provides specific implementations of the Implementor interface.

#include <iostream>
#include <memory>

// Implementor Interface
class TV {
public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void setChannel(int channel) = 0;
    virtual ~TV() = default;
};

class SonyTV : public TV {
public:
    void on() override {
        std::cout << "Sony TV is ON\n";
    }

    void off() override {
        std::cout << "Sony TV is OFF\n";
    }

    void setChannel(int channel) override {
        std::cout << "Sony TV set to channel " << channel << "\n";
    }
};

class SamsungTV : public TV {
public:
    void on() override {
        std::cout << "Samsung TV is ON\n";
    }

    void off() override {
        std::cout << "Samsung TV is OFF\n";
    }

    void setChannel(int channel) override {
        std::cout << "Samsung TV set to channel " << channel << "\n";
    }
};

class RemoteControl {
protected:
    std::shared_ptr<TV> tv; // Bridge to the implementation

public:
    explicit RemoteControl(std::shared_ptr<TV> tv) : tv(std::move(tv)) {}

    virtual void turnOn() {
        tv->on();
    }

    virtual void turnOff() {
        tv->off();
    }

    virtual void setChannel(int channel) {
        tv->setChannel(channel);
    }

    virtual ~RemoteControl() = default;
};

class AdvancedRemoteControl : public RemoteControl {
public:
    explicit AdvancedRemoteControl(std::shared_ptr<TV> tv) : RemoteControl(std::move(tv)) {}

    void setFavoriteChannel() {
        std::cout << "Setting to favorite channel: 10\n";
        tv->setChannel(10);
    }
};

int main() {
    // Create TV implementations
    auto sony = std::make_shared<SonyTV>();
    auto samsung = std::make_shared<SamsungTV>();

    // Use a basic remote with Sony TV
    RemoteControl basicRemote(sony);
    basicRemote.turnOn();
    basicRemote.setChannel(5);
    basicRemote.turnOff();

    // Use an advanced remote with Samsung TV
    AdvancedRemoteControl advancedRemote(samsung);
    advancedRemote.turnOn();
    advancedRemote.setFavoriteChannel();
    advancedRemote.turnOff();

    return 0;
}


//Sony TV is ON
//Sony TV set to channel 5
//Sony TV is OFF
//Samsung TV is ON
//Setting to favorite channel: 10
//Samsung TV set to channel 10
//Samsung TV is OFF


//Key Features of the Bridge Pattern
//Decoupling:
//Separates the abstraction and implementation, allowing them to change independently.
//Flexibility:
//New abstractions or implementations can be added without affecting each other.
//Scalability:
//Supports variations of both abstraction and implementation.
//Real-World Applications
//Device Control:
//Remote controls for various devices (TVs, lights, air conditioners).
//Graphics Rendering:
//Separating shape abstractions (circle, rectangle) from rendering implementations (OpenGL, DirectX).
//Cross-Platform Development:
//Decoupling platform-specific code from application logic.
//Caveats
//Increased Complexity:
//Adds layers of abstraction and indirection, which might be overkill for simple use cases.
//Overhead:
//Introduces additional references and delegation.
