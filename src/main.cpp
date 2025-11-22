#include "Model.hpp"
#include "view.hpp"
#include "ObjectType.hpp"
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!", sf::Style::Close);
    Model model(6, 6);
    View view{model, window};
    model.attach(&view);
    model.grid[5][5].push_back(ObjectType::BABA);
    model.notify();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        view.draw();
        window.display();
    }
    return 0;
}