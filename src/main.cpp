#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"
//#include "ObjectType.hpp"
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window{sf::VideoMode(800, 800), "SFML works!", sf::Style::Close};
    sf::Event event{};
    Model model{"assets/1.txt"};
    View view{model, window};
    Controller controller{};

    //Model model{path};
    //Model model(6, 6);
    //View view{model, window};
    //model.attach(&view);
    //model.grid[5][5].push_back(ObjectType::BABA);
    //model.notify();

    while (window.isOpen())
    {
        controller.handleEvent(event, window, model);
        view.update(model);
        window.clear();
        view.draw(window);
        window.display();
    }

    return 0;
}
