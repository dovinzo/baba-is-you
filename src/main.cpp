#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window{sf::VideoMode(800, 800), "Baba Is You", sf::Style::Close};
    sf::Event event;
    Model model{"assets/levelTest.txt"};
    Controller controller;
    View view{model, window};

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        controller.handleEvent(model, event, window);
        view.update(model);
        window.clear();
        view.draw(window);
        window.display();
    }

    return 0;
}
