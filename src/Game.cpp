#include "Game.hpp"

Game::Game(const std::string& title, unsigned int width, unsigned int height, sf::ContextSettings settings)
    : m_window{sf::VideoMode{width, height}, title, sf::Style::Default, settings}, m_running{false}
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
            } else {
                handleWindowEvent(event);
            }
        }

        auto delta = clock.restart();
        update(delta);
        render();

        m_window.display();
    }

    cleanup();
}

void Game::stop()
{
    m_running = false;
}

bool Game::isRunning() const
{
    return m_running;
}