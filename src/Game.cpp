#include "Game.hpp"

Game::Game(const std::string& title, unsigned int width, unsigned int height)
    : m_window{sf::VideoMode{width, height}, title}, m_running{false}
{

}

void Game::run()
{
    m_window.setActive();
    
    if(!init()) {
        return;
    }

    m_running = true;

    sf::Clock clock;
    while(isRunning()) {
        sf::Event event;

        while(m_window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                stop();
            }
        }

        auto delta = clock.restart();
        update(delta);
        render();

        m_window.display();
    }
}

void Game::stop()
{
    m_running = false;
}

bool Game::isRunning() const
{
    return m_running;
}