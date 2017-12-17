#ifndef GAME_HPP
#define GAME_HPP
#pragma once

#include <SFML/Window.hpp>

#include <string>

class Game 
{
public:
    Game(const std::string& title, unsigned int width, unsigned int height);
    virtual ~Game() {}

    void run();
    void stop();

    bool isRunning() const;

protected:
    virtual bool init() { return true; }
    virtual void update(sf::Time& delta) {}
    virtual void render() = 0;
    virtual void cleanup() {}
    virtual void handleWindowEvent(sf::Event& event) {}

private:
    sf::Window m_window;
    bool m_running;
};

#endif // GAME_HPP