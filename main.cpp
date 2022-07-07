#include <SFML/Graphics.hpp>

int main()
{
    // Creation of the window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!",sf::Style::Fullscreen);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    //creation of the event
    sf::Event event;

    // Game loop
    while (window.isOpen())
    {

        while (window.pollEvent(event))
        {
            // closing the window and ending the game
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();
            }
        }

        // TODO Updating the Game


        // Clearing the old frame and preparing for drawing the new onr
        window.clear();

        // Drawing all the objects of the game
        window.draw(shape);// TODO change once created the game class

        // Bring to screen and display the new frame just drawn
        window.display();
    }

    // End of the Game
    return 0;
}