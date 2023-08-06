#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <random>

class Ball
{
private:
    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::CircleShape c;

public:
    Ball(float pos_x, float pos_y, float vel_x, float vel_y)
    {
        pos.x = pos_x;
        pos.y = pos_y;
        vel.x = vel_x;
        vel.y = vel_y;
    }

    sf::Vector2f get_position() { return pos; }

    void set_position(float pos_x, float pos_y) 
    { 
        pos.x = pos_y; 
        pos.y = pos_y; 
    }

    void set_velocity(float vel_x, float vel_y)
    {
        vel.x = vel_y;
        vel.y = vel_y;
    }

    void render_ball(sf::RenderWindow& window) 
    {
        c.setPosition(pos);
        c.setRadius(8);
        window.draw(c);
    }
};

class Paddle 
{
private:
    sf::Vector2f pos;
    sf::RectangleShape r;

public:
    Paddle(float pos_x, float pos_y)
    {
        pos.x = pos_x;
        pos.y = pos_y;
    }

    sf::Vector2f get_position() { return pos; }

    void set_position(float pos_x, float pos_y)
    {
        pos.x += pos_y;
        pos.y += pos_y;
    }

    void move_paddle(float move_y)
    {
        pos.y += move_y;
    }

    void ai_paddle(Ball& b)
    {
        //Generate random number from -10 to 10
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<> dist(-10, 10);

        //Set position = ball position + random offset number
        pos.y += ((dist(mt)) + b.get_position().y);
    }

    void render_paddle(sf::RenderWindow& window)
    {
        r.setPosition(pos);
        r.setSize(sf::Vector2f(12, 180));
        window.draw(r);
    }

};

class Game
{
private:
    int lscore;
    int rscore;
    int winner;

public:
    Game(Paddle& lpaddle, Paddle& rpaddle, Ball& ball, sf::RenderWindow& window) 
    {
        lscore = 0;
        rscore = 0;
        winner = 0;
    };

    

    ~Game() {};
};

int main()
{
    int window_width = 1000;
    int window_height = 800;

	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML window");

    Ball ball(window_width / 2, window_height / 2, 0, 0);

    Paddle lpaddle(100, 300);
    Paddle rpaddle(900, 300);

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape) window.close();

                else if (event.key.code == sf::Keyboard::Up) rpaddle.move_paddle(-10);

                else if (event.key.code == sf::Keyboard::Down) rpaddle.move_paddle(10);

                else if (event.key.code == sf::Keyboard::W) lpaddle.move_paddle(-10);

                else if (event.key.code == sf::Keyboard::S) lpaddle.move_paddle(10);
            }
        }

        // Clear screen
        window.clear();

        ball.render_ball(window);
        lpaddle.render_paddle(window);
        rpaddle.render_paddle(window);

        // Update the window
        window.display();
    }

}
