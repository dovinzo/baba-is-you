#include "view.hpp"
#include "IReadOnlyModel.hpp"
#include "ObjectType.hpp"
#include <iostream>

View::View(const IReadOnlyModel& iReadOnlyModel, sf::RenderWindow& window) : iReadOnlyModel{iReadOnlyModel}, window{window}
{
    loadTextures();
    createSprites();
}

void View::update()
{
    int width_window = (int)(window.getSize().x);
    int height_window = (int)(window.getSize().y);
    int width_grid = iReadOnlyModel.getWidth();
    int height_grid = iReadOnlyModel.getHeight();
    float scale_x = (float)(width_window) / (24.f * (float)(width_grid));
    float scale_y = (float)(height_window) / (24.f * (float)(height_grid));
    for (int x = 0 ; x < width_grid ; x++)
    {
        for (int y = 0 ; y < height_grid ; y++)
        {
            for (ObjectType object_type : iReadOnlyModel.cell(x, y))
            {
                if (object_type == ObjectType::BABA)
                {
                    baba_sprite.setPosition(24 * scale_x * x, 24 * scale_y * y);
                    baba_sprite.setScale(scale_x, scale_y);
                }
            }
        }
    }
}

void View::loadTextures()
{
    baba_texture.loadFromFile("assets/baba.png");
}

void View::createSprites()
{
    baba_sprite.setTexture(baba_texture);
    baba_sprite.setPosition(0, 0);
    baba_sprite.setScale(1.f, 2.f);
    baba_sprite.setTextureRect(sf::IntRect(1, 1, 24, 24));
}

void View::draw()
{
    window.draw(baba_sprite);
}