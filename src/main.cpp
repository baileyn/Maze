#include <glad/glad.h>
#include "Game.hpp"

class SimpleGame : public Game
{
public:
    SimpleGame() 
        : Game{"Window title", 800, 600}
    {
    }

protected:
    bool init()
    {
        if(!gladLoadGL()) {
            return false;
        }

        glClearColor(1, 0, 0, 1);
        return true;
    }

    void render()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
};

int main(int argc, char** argv)
{
    SimpleGame game{};
    game.run();
}