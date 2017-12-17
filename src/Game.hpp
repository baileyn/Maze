#ifndef GAME_HPP
#define GAME_HPP
#pragma once

#include <SFML/Window.hpp>

#include <string>

class Game 
{
public:
    /**
     * @brief Constructs a new Game with the specified title, width, and height.
     * 
     * @param title the title of the window to open.
     * @param width the width of the inner window.
     * @param height the height of the inner window.
     */
    Game(const std::string& title, unsigned int width, unsigned int height);
    virtual ~Game() {}

    /**
     * @brief starts the Game's main loop.
     */
    void run();

    /**
     * @brief signals the Game to stop running. This causes cleanup() to be called, and 
     *        the window to be destroyed. NOTE: OpenGL Context still exists during cleanup.
     */
    void stop();

    /**
     * @brief determines whether or not the Game is running.
     * 
     * @return true if the Game is running.
     * @return false if the Game isn't running.
     */
    bool isRunning() const;

protected:
    /**
     * @brief the function that is called after the Window has been created and an OpenGL
     *        context has been established. If this function returns false, the Game will 
     *        not start to run.
     * 
     * @return true if initialization was successful.
     * @return false if there was a problem in initialization.
     */
    virtual bool init() { return true; }

    /**
     * @brief called every frame to update entities in the Game.
     * 
     * @param delta the time since the last invocation of update.
     */
    virtual void update(sf::Time& delta) {}

    /**
     * @brief called every frame to render the entities in the Game.
     */
    virtual void render() = 0;

    /**
     * @brief called whenever the Game state is flagged to stop running. Used to
     *        clean up any resources allocated in init().
     */
    virtual void cleanup() {}

    /**
     * @brief A function that's called to handle Window events. NOTE: sf::Event::Closed is
     *        handled by the main Game loop to trigger the game to stop running.
     *
     * @param event the Event sent to the Window.
     */
    virtual void handleWindowEvent(sf::Event& event) {}

private:
    sf::Window m_window;
    bool m_running;
};

#endif // GAME_HPP