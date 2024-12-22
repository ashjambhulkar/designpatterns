//
//  adapter.cpp
//  designpatterns
//
//  Created by Ashish Jambhulkar on 12/22/24.
//

//The Adapter Design Pattern is a structural design pattern that allows incompatible interfaces to work together. It acts as a bridge between two incompatible classes by translating the interface of one class into an interface that another class expects.
//
//Intuitive Analogy
//Imagine you buy a new electronic device from a foreign country. However, the power plug doesn’t fit into your local sockets because the shapes are incompatible. Instead of replacing the device or socket, you use a power adapter to bridge the gap.
//
//Similarly, in programming:
//
//The existing class (foreign plug) has an interface that doesn’t match the client’s expectations (local socket).
//The adapter translates between the two so they can work together.
//Components of the Adapter Pattern
//Target Interface:
//Defines the interface expected by the client.
//Adaptee:
//The existing class that needs to be adapted.
//Adapter:
//The class that bridges the gap between the Target and the Adaptee.
//Client:
//Uses the Target Interface to interact with the Adapter.


#include <iostream>
#include <string>

// Target Interface
class MediaPlayer {
public:
    virtual void play(const std::string& audioType, const std::string& fileName) = 0;
    virtual ~MediaPlayer() = default;
};

class AdvancedMediaPlayer {
public:
    virtual void playVlc(const std::string& fileName) {
        std::cout << "Playing VLC file: " << fileName << std::endl;
    }

    virtual void playMp4(const std::string& fileName) {
        std::cout << "Playing MP4 file: " << fileName << std::endl;
    }

    virtual ~AdvancedMediaPlayer() = default;
};

class MediaAdapter : public MediaPlayer {
private:
    AdvancedMediaPlayer* advancedPlayer;

public:
    explicit MediaAdapter(const std::string& audioType) {
        if (audioType == "vlc") {
            advancedPlayer = new AdvancedMediaPlayer();
        } else if (audioType == "mp4") {
            advancedPlayer = new AdvancedMediaPlayer();
        } else {
            advancedPlayer = nullptr;
        }
    }

    void play(const std::string& audioType, const std::string& fileName) override {
        if (audioType == "vlc") {
            advancedPlayer->playVlc(fileName);
        } else if (audioType == "mp4") {
            advancedPlayer->playMp4(fileName);
        } else {
            std::cout << "Unsupported format: " << audioType << std::endl;
        }
    }

    ~MediaAdapter() {
        delete advancedPlayer;
    }
};

class AudioPlayer : public MediaPlayer {
private:
    MediaAdapter* adapter;

public:
    void play(const std::string& audioType, const std::string& fileName) override {
        if (audioType == "mp3") {
            std::cout << "Playing MP3 file: " << fileName << std::endl;
        } else if (audioType == "vlc" || audioType == "mp4") {
            adapter = new MediaAdapter(audioType);
            adapter->play(audioType, fileName);
            delete adapter;
        } else {
            std::cout << "Unsupported format: " << audioType << std::endl;
        }
    }
};

int main() {
    AudioPlayer player;

    player.play("mp3", "song.mp3");      // Output: Playing MP3 file: song.mp3
    player.play("mp4", "movie.mp4");    // Output: Playing MP4 file: movie.mp4
    player.play("vlc", "video.vlc");    // Output: Playing VLC file: video.vlc
    player.play("avi", "clip.avi");     // Output: Unsupported format: avi

    return 0;
}

//Key Features of the Adapter Pattern
//Interface Translation:
//Allows incompatible interfaces to work together without modifying existing code.
//Single Responsibility Principle:
//The Adapter handles the translation, leaving the client and adaptee unchanged.
//Flexibility:
//You can introduce new adapters for different interfaces without altering the core client or adaptee code.
//Real-World Applications
//Legacy Code Integration:
//Bridging modern systems with older libraries or APIs.
//Cross-Platform Compatibility:
//Adapting code to work on multiple platforms or operating systems.
//External Libraries:
//Wrapping third-party libraries to conform to your application’s interfaces.
//Caveats
//Increased Complexity:
//Introducing adapters adds an extra layer of indirection.
//Overhead:
//Adapter usage might add runtime overhead, especially in performance-critical systems.
