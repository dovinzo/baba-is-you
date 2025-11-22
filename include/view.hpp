#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>
#include "IReadOnlyModel.hpp"
#include "IObserver.hpp"

class View : public IObserver
{
    public:
        View(const IReadOnlyModel& iReadOnlyModel, sf::RenderWindow& window);
        virtual void update() override;
        void draw();
    private:
        void loadTextures();
        void createSprites();
    private:
        sf::IntRect baba_rectangle;
        sf::Texture baba_texture;
        sf::Sprite baba_sprite;
        const IReadOnlyModel& iReadOnlyModel;
        sf::RenderWindow& window;
};

#endif