//
//  proxy.cpp
//  designpatterns
//
//  Created by Ashish Jambhulkar on 12/22/24.
//

//The Proxy Design Pattern is a structural design pattern that provides a placeholder or surrogate object to control access to another object. The proxy can add functionality such as lazy initialization, access control, logging, or caching, while keeping the interface identical to the real object.
//
//Intuitive Analogy
//Think of a personal assistant working for a celebrity:
//
//The assistant acts as a proxy, managing access to the celebrity.
//If a fan wants an autograph, they must go through the assistant.
//The assistant controls access, handles scheduling, and filters out unimportant requests, but doesn’t change how the fan interacts (e.g., by presenting the celebrity's signature).
//In programming:
//
//The real object is the celebrity.
//The proxy is the assistant, controlling access to the real object.
//Types of Proxies
//Virtual Proxy:
//Manages expensive resources and creates them only when needed (lazy initialization).
//Protection Proxy:
//Controls access, ensuring only authorized entities can interact with the real object.
//Remote Proxy:
//Provides a local representation of an object that exists in a remote location (e.g., on a server).
//Logging/Smart Proxy:
//Adds functionality like logging, monitoring, or caching.


#include <iostream>
#include <string>

// Subject Interface
class Image {
public:
    virtual void display() = 0; // Common method for both real and proxy
    virtual ~Image() = default;
};

class RealImage : public Image {
private:
    std::string fileName;

public:
    explicit RealImage(const std::string& file) : fileName(file) {
        loadFromDisk(fileName); // Simulate expensive operation
    }

    void display() override {
        std::cout << "Displaying image: " << fileName << "\n";
    }

private:
    void loadFromDisk(const std::string& file) {
        std::cout << "Loading image from disk: " << file << "\n";
    }
};

class ProxyImage : public Image {
private:
    std::string fileName;
    RealImage* realImage; // Pointer to the real object

public:
    explicit ProxyImage(const std::string& file) : fileName(file), realImage(nullptr) {}

    void display() override {
        if (!realImage) {
            realImage = new RealImage(fileName); // Lazy initialization
        }
        realImage->display();
    }

    ~ProxyImage() {
        delete realImage; // Clean up real object
    }
};

int main() {
    // Create a proxy for an image
    ProxyImage proxyImage("test_image.jpg");

    // Image is not loaded until display() is called
    std::cout << "Image is not yet loaded.\n";
    proxyImage.display(); // Load and display the image
    proxyImage.display(); // Image is already loaded; just display it

    return 0;
}

//Image is not yet loaded.
//Loading image from disk: test_image.jpg
//Displaying image: test_image.jpg
//Displaying image: test_image.jpg


//Key Features of the Proxy Pattern
//Encapsulation of Access:
//Controls access to the real object while keeping the interface consistent.
//Delayed Initialization:
//Creates expensive objects only when they are needed (virtual proxy).
//Additional Functionality:
//Can add features like caching, logging, or security checks.
//Real-World Applications
//Virtual Proxy:
//Image viewers that load high-resolution images only when displayed.
//Protection Proxy:
//Role-based access control systems where sensitive operations are restricted.
//Remote Proxy:
//Distributed systems, where the proxy represents objects on remote servers.
//Smart Proxy:
//Adding logging, usage statistics, or monitoring functionality to objects.
//Caveats
//Overhead:
//Adds an additional layer of indirection, which may affect performance.
//Complexity:
//Requires extra classes and logic to implement the proxy functionality.
