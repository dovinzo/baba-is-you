#include "MenuView.hpp"

MenuView::MenuView(sf::RenderWindow& window, MenuModel& menuModel): font{}, level1{}, level2{}, level3{}, window{window}, menuModel{menuModel}
{
    font.loadFromFile("assets/Serif.ttf");

    level1.setFont(font);
    level1.setString("NIVEAU 1");
    level1.setPosition(100, 150);

    level2.setFont(font);
    level2.setString("NIVEAU 2");
    level2.setPosition(100, 350);

    level3.setFont(font);
    level3.setString("NIVEAU 3");
    level3.setPosition(100, 550);

    this->update();
}

void MenuView::draw()
{
    window.draw(level1);
    window.draw(level2);
    window.draw(level3);
}

void MenuView::update()
{
    this->reset();
    switch (menuModel.getMenuItem())
    {
        case MenuItem::LEVEL1:
            level1.setFillColor(sf::Color::Red);
            break;
        case MenuItem::LEVEL2:
            level2.setFillColor(sf::Color::Red);
            break;
        case MenuItem::LEVEL3:
            level3.setFillColor(sf::Color::Red);
            break;
    }
}

void MenuView::reset()
{
    level1.setFillColor(sf::Color::White);
    level2.setFillColor(sf::Color::White);
    level3.setFillColor(sf::Color::White);
}
