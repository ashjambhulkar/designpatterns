//
//  facade.cpp
//  designpatterns
//
//  Created by Ashish Jambhulkar on 12/22/24.
//

//The Facade Design Pattern is a structural design pattern that provides a simplified interface to a complex system of classes, libraries, or frameworks. It’s like a "front-facing" interface that hides the complexities of the subsystem, making it easier for clients to interact with.
//
//Intuitive Analogy
//Think of a restaurant:
//
//A customer interacts with the waiter (facade) to place an order.
//The waiter takes the order and interacts with the kitchen, billing, and serving staff (subsystems).
//The customer doesn’t need to deal with the complexities of how the kitchen prepares the food or how the billing system calculates the total.
//In programming, the Facade acts like the waiter:
//
//It provides a simple interface (e.g., "placeOrder") that hides the complexities of multiple subsystems.
//Components of the Facade Pattern
//Subsystems:
//A set of classes or modules that perform the actual work.
//These classes have complex interfaces or interdependencies.
//Facade:
//A wrapper class that provides a simplified interface to the subsystems.
//Client:
//Interacts with the facade instead of directly interacting with subsystems.

#include <iostream>
#include <string>

class DVDPlayer {
public:
    void on() {
        std::cout << "DVD Player is ON.\n";
    }

    void play(const std::string& movie) {
        std::cout << "Playing movie: " << movie << "\n";
    }

    void off() {
        std::cout << "DVD Player is OFF.\n";
    }
};

class SoundSystem {
public:
    void on() {
        std::cout << "Sound System is ON.\n";
    }

    void setVolume(int level) {
        std::cout << "Setting volume to " << level << ".\n";
    }

    void off() {
        std::cout << "Sound System is OFF.\n";
    }
};

class Projector {
public:
    void on() {
        std::cout << "Projector is ON.\n";
    }

    void setInput(const std::string& source) {
        std::cout << "Setting projector input to " << source << ".\n";
    }

    void off() {
        std::cout << "Projector is OFF.\n";
    }
};

class HomeTheaterFacade {
private:
    DVDPlayer* dvdPlayer;
    SoundSystem* soundSystem;
    Projector* projector;

public:
    HomeTheaterFacade(DVDPlayer* dvd, SoundSystem* sound, Projector* proj)
        : dvdPlayer(dvd), soundSystem(sound), projector(proj) {}

    void watchMovie(const std::string& movie) {
        std::cout << "Preparing to watch movie: " << movie << "\n";
        projector->on();
        projector->setInput("DVD");
        soundSystem->on();
        soundSystem->setVolume(20);
        dvdPlayer->on();
        dvdPlayer->play(movie);
        std::cout << "Enjoy your movie!\n";
    }

    void endMovie() {
        std::cout << "Shutting down the home theater.\n";
        dvdPlayer->off();
        soundSystem->off();
        projector->off();
    }
};

int main() {
    // Create subsystem components
    DVDPlayer dvd;
    SoundSystem sound;
    Projector projector;

    // Create the facade
    HomeTheaterFacade homeTheater(&dvd, &sound, &projector);

    // Use the facade to simplify interactions
    homeTheater.watchMovie("Inception");
    homeTheater.endMovie();

    return 0;
}

//Preparing to watch movie: Inception
//Projector is ON.
//Setting projector input to DVD.
//Sound System is ON.
//Setting volume to 20.
//DVD Player is ON.
//Playing movie: Inception
//Enjoy your movie!
//Shutting down the home theater.
//DVD Player is OFF.
//Sound System is OFF.
//Projector is OFF.


//Key Features of the Facade Pattern
//Simplifies Complex Interfaces:
//Provides a single, easy-to-use interface to interact with multiple subsystems.
//Encapsulation:
//Hides the complexities of the underlying subsystems from the client.
//Improves Maintainability:
//Centralizes subsystem interactions, making code easier to update or extend.
//Real-World Applications
//GUI Frameworks:
//Complex graphical components (e.g., buttons, windows) are often wrapped in a simple facade interface.
//Networking Libraries:
//Complex protocols (e.g., HTTP, FTP) are hidden behind simple APIs.
//Game Engines:
//Subsystems like physics, rendering, and audio are managed through a unified interface.
//Caveats
//Overhead:
//Adding a facade may introduce an additional layer of indirection.
//Inflexibility:
//Facades provide a fixed interface, which might not expose all subsystem functionality.
