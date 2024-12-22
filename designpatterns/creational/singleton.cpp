//
//  singleton.cpp
//  designpatterns
//
//  Created by Ashish Jambhulkar on 12/22/24.
//


//
//The Singleton Design Pattern is a creational design pattern that ensures a class has only one instance and provides a global point of access to it. Let’s break it down with analogies, technical details, and an example in C++.
//
//Intuitive Analogy
//Imagine a government office issuing passports. There’s only one official seal that validates a passport. It ensures no duplicate seals are used, preventing forgery. Every time a passport needs validation, the same seal is used.
//
//The Singleton Pattern works similarly:
//
//It ensures that only one instance of a class exists (like the official seal).
//It provides a global access point to use that single instance (like calling for the seal when needed).
//Technical Explanation
//The Singleton Pattern:
//
//Restricts Instantiation: Ensures only one instance of the class exists throughout the application.
//Global Access Point: Provides a static method to retrieve the single instance.
//Why Use Singleton?
//Resource Management: For managing shared resources like database connections, logging services, or configuration settings.
//Controlled Access: Centralized access to a resource ensures consistency and prevents duplication.
//Lazy Initialization: Singleton can create the instance only when it is first needed.


#include <iostream>

class Singleton {
private:
    // Static pointer to the single instance
    static Singleton* instance;

    // Private constructor to prevent direct instantiation
    Singleton() {
        std::cout << "Singleton instance created.\n";
    }

public:
    // Delete copy constructor and assignment operator to prevent copying
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // Static method to provide access to the instance
    static Singleton* getInstance() {
        if (instance == nullptr) { // Lazy initialization
            instance = new Singleton();
        }
        return instance;
    }

    void displayMessage() {
        std::cout << "This is the Singleton instance.\n";
    }
};

// Initialize static member
Singleton* Singleton::instance = nullptr;

int main() {
    // Access the Singleton instance
    Singleton* s1 = Singleton::getInstance();
    s1->displayMessage();

    // Attempting to create another instance still returns the same object
    Singleton* s2 = Singleton::getInstance();
    if (s1 == s2) {
        std::cout << "Both instances are the same.\n";
    }

    return 0;
}

//
//Key Elements of the Code
//Private Constructor: Prevents creating instances using new.
//Static Instance: Stores the single instance of the class.
//Lazy Initialization: Creates the instance only when getInstance() is called for the first time.
//Copy Prevention: Disables the copy constructor and assignment operator to avoid duplication.


//Multithreaded Singleton
//In multithreaded applications, the Singleton pattern needs thread safety.


#include <iostream>
#include <mutex>

class ThreadSafeSingleton {
private:
    static ThreadSafeSingleton* instance;
    static std::mutex mtx;

    ThreadSafeSingleton() {
        std::cout << "Thread-safe Singleton instance created.\n";
    }

public:
    ThreadSafeSingleton(const ThreadSafeSingleton&) = delete;
    ThreadSafeSingleton& operator=(const ThreadSafeSingleton&) = delete;

    static ThreadSafeSingleton* getInstance() {
        std::lock_guard<std::mutex> lock(mtx); // Lock for thread safety
        if (instance == nullptr) {
            instance = new ThreadSafeSingleton();
        }
        return instance;
    }

    void displayMessage() {
        std::cout << "This is the thread-safe Singleton instance.\n";
    }
};

ThreadSafeSingleton* ThreadSafeSingleton::instance = nullptr;
std::mutex ThreadSafeSingleton::mtx;

int main() {
    // Example usage of ThreadSafeSingleton
    ThreadSafeSingleton* s1 = ThreadSafeSingleton::getInstance();
    s1->displayMessage();

    return 0;
}


//Advantages of Singleton
//Controlled Access: Ensures only one instance exists, avoiding resource duplication.
//Global Access Point: Simplifies access to shared resources like configuration files or logs.
//Lazy Initialization: Resources are initialized only when needed.
//Disadvantages of Singleton
//Hidden Dependencies: Overuse can lead to tightly coupled code.
//Difficulty in Testing: Global state managed by Singleton can make testing harder.
//Thread Safety: Needs extra care to handle concurrent access.
