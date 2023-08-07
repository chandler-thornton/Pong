#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <random>

const int window_width = 1000;
const int window_height = 800;

class Ball
{
private:
    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::CircleShape c;

public:
    Ball()
    {
        pos.x = 0;
        pos.y = 0;
        vel.x = 0;
        vel.y = 0;
    }

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

    void move_ball()
    {
        pos.x += vel.x;
        pos.y += vel.y;
    }

    void render_ball(sf::RenderWindow& window)
    {
        c.setPosition(pos);
        c.setRadius(8);
        window.draw(c);
    }

    void is_touching_wall()
    {
        if (int(pos.y) == 0 || int(pos.y) == 800)
        {
            std::cout << vel.y;
            vel.y = -1.f * vel.y;
        }
    }

    void off_screen(Ball& b)
    {
        if (pos.x < 0 || pos.x > 1000)
        {
            b.set_position(window_width / 2, window_height / 2);
        }
    }

};

class Paddle
{
private:
    sf::Vector2f pos;
    sf::RectangleShape r;

public:
    Paddle()
    {
        pos.x = 0;
        pos.y = 0;
    }

    Paddle(float pos_x, float pos_y)
    {
        pos.x = pos_x;
        pos.y = pos_y;
    }

    sf::Vector2f get_position() { return pos; }

    void set_position(float pos_x, float pos_y)
    {
        pos.x += pos_x;
        pos.y += pos_y;
    }

    void move_paddle(float move_y)
    {
        pos.y += move_y;
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
    int ai_score = 0;
    int player_score = 0;
    int winner = 2;

    Paddle lpaddle;
    Paddle rpaddle;
    Ball ball;

public:
    Game() 
    {
        ball.set_position(window_width / 2, window_height / 2);
        ball.set_velocity(0.2, 0.2);

        lpaddle.set_position(100, 300);
        rpaddle.set_position(900, 300);
    }

    void game_loop(sf::RenderWindow& window)
    {
        while (window.isOpen())
        {
            // Process input events
            sf::Event event;
            while (window.pollEvent(event))
            {
                // Close window: exit
                if (event.type == sf::Event::Closed) window.close();

                if (event.type == sf::Event::KeyPressed)
                {
                    //Close window when escape key pressed
                    if (event.key.code == sf::Keyboard::Escape) window.close();

                    //Right paddle manual controls
                    else if (event.key.code == sf::Keyboard::Up) rpaddle.move_paddle(-25);

                    else if (event.key.code == sf::Keyboard::Down) rpaddle.move_paddle(25);

                    //Left paddle manual controls
                    else if (event.key.code == sf::Keyboard::W) lpaddle.move_paddle(-25);

                    else if (event.key.code == sf::Keyboard::S) lpaddle.move_paddle(25);
                }
            }

            ball.is_touching_wall();
            ball.off_screen(ball);
            std::cout << ball.get_position().y << std::endl;
            ball.move_ball();

            // Clear screen
            window.clear();

            //Renders
            ball.render_ball(window);
            lpaddle.render_paddle(window);
            rpaddle.render_paddle(window);

            // Update the window
            window.display();
        }
        winner = (ai_score > player_score) ? 0 : 1;
    }

    
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML window");

    std::vector<Game> games;

    games.push_back(Game());
    games[games.size() - 1].game_loop(window);
}
