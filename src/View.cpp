#include "View.hpp"
#include "Model.hpp"
#include "BoardElement.hpp"
#include "Enums.hpp"
#include <unordered_map>

View::View(Model& model, sf::RenderWindow& window) : textures{}, sprites{}, model{model}, window{window}
{
    this->createTextures();
    this->createSprites();
}

View::~View()
{
    std::unordered_map<BoardElementType, sf::Texture*>::iterator it_textures = textures.begin();
    while (it_textures != textures.end())
    {
        delete it_textures->second;
        it_textures = textures.erase(it_textures);
    }

    std::unordered_map<BoardElement*, sf::Sprite*>::iterator it_sprites = sprites.begin();
    while (it_sprites != sprites.end())
    {
        delete it_sprites->second;
        it_sprites = sprites.erase(it_sprites);
    }
}

void View::update()
{
    int width{model.getBoardWidth()};
    int height{model.getBoardHeight()};
    std::vector<BoardElement*> cell;
    float s{};
    int xScreen{};
    int yScreen{};
    s = (height < width) ? (800.f / (24.f * (float)width)) : (800.f / (24.f * (float)height));
    for (int x = 0 ; x < width ; x++)
    {
        xScreen = (int)(24.f * s * (float)(x));
        for (int y = 0 ; y < height ; y++)
        {
            yScreen = (int)(24.f * s * (float)(y));
            cell = model.getBoardCell(x, y);
            for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
            {
                sprites[cell[i]]->setPosition(xScreen, yScreen);
            }
        }
    }
}

void View::draw()
{
    std::vector<BoardElement*> cell;
    for (int x = 0 ; x < model.getBoardWidth() ; x++)
    {
        for (int y = 0 ; y < model.getBoardHeight() ; y++)
        {
            cell = model.getBoardCell(x, y);
            for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
            {
                window.draw(*sprites[cell[i]]);
            }
        }
    }
}

void View::createTextures()
{
    // baba
    textures[BoardElementType::BABA] = new sf::Texture{};
    textures[BoardElementType::BABA]->loadFromFile("assets/baba.png");
    // rock
    textures[BoardElementType::ROCK] = new sf::Texture{};
    textures[BoardElementType::ROCK]->loadFromFile("assets/rock.png");
    // flag
    textures[BoardElementType::FLAG] = new sf::Texture{};
    textures[BoardElementType::FLAG]->loadFromFile("assets/flag.png");
    // wall
    textures[BoardElementType::WALL] = new sf::Texture{};
    textures[BoardElementType::WALL]->loadFromFile("assets/wall.png");
    // text is
    textures[BoardElementType::TEXT_IS] = new sf::Texture{};
    textures[BoardElementType::TEXT_IS]->loadFromFile("assets/text_is.png");
    // text baba
    textures[BoardElementType::TEXT_BABA] = new sf::Texture{};
    textures[BoardElementType::TEXT_BABA]->loadFromFile("assets/text_baba.png");
    // text you
    textures[BoardElementType::TEXT_YOU] = new sf::Texture{};
    textures[BoardElementType::TEXT_YOU]->loadFromFile("assets/text_you.png");
    // text wall
    textures[BoardElementType::TEXT_WALL] = new sf::Texture{};
    textures[BoardElementType::TEXT_WALL]->loadFromFile("assets/text_wall.png");
    // text push
    textures[BoardElementType::TEXT_PUSH] = new sf::Texture{};
    textures[BoardElementType::TEXT_PUSH]->loadFromFile("assets/text_push.png");
    // text flag
    textures[BoardElementType::TEXT_FLAG] = new sf::Texture{};
    textures[BoardElementType::TEXT_FLAG]->loadFromFile("assets/text_flag.png");
    // text win
    textures[BoardElementType::TEXT_WIN] = new sf::Texture{};
    textures[BoardElementType::TEXT_WIN]->loadFromFile("assets/text_win.png");
    // text rock
    textures[BoardElementType::TEXT_ROCK] = new sf::Texture{};
    textures[BoardElementType::TEXT_ROCK]->loadFromFile("assets/text_rock.png");
    // text stop
    textures[BoardElementType::TEXT_STOP] = new sf::Texture{};
    textures[BoardElementType::TEXT_STOP]->loadFromFile("assets/text_stop.png");
}

void View::createSprites()
{
    std::vector<BoardElement*> cell;
    for (int x = 0 ; x < model.getBoardWidth() ; x++)
    {
        for (int y = 0 ; y < model.getBoardHeight() ; y++)
        {
            cell = model.getBoardCell(x, y);
            for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
            {
                this->createSprite(cell[i]);
            }
        }
    }
}

void View::createSprite(BoardElement* boardElement)
{
    int xGrid{boardElement->getPositionX()}, yGrid{boardElement->getPositionY()};
    int xScreen{View::convertXGridToXScreen(xGrid)}, yScreen{View::convertYGridToYScreen(yGrid)};
    float s{View::calculateSpritesScale()};
    sprites[boardElement] = new sf::Sprite{};
    switch (boardElement->getType())
    {
        case BoardElementType::BABA:
            sprites[boardElement]->setTexture(*textures[BoardElementType::BABA]);
            break;
        case BoardElementType::WALL:
            sprites[boardElement]->setTexture(*textures[BoardElementType::WALL]);
            break;
        case BoardElementType::FLAG:
            sprites[boardElement]->setTexture(*textures[BoardElementType::FLAG]);
            break;
        case BoardElementType::ROCK:
            sprites[boardElement]->setTexture(*textures[BoardElementType::ROCK]);
            break;
        case BoardElementType::TEXT_BABA:
            sprites[boardElement]->setTexture(*textures[BoardElementType::TEXT_BABA]);
            break;
        case BoardElementType::TEXT_WALL:
            sprites[boardElement]->setTexture(*textures[BoardElementType::TEXT_WALL]);
            break;
        case BoardElementType::TEXT_FLAG:
            sprites[boardElement]->setTexture(*textures[BoardElementType::TEXT_FLAG]);
            break;
        case BoardElementType::TEXT_ROCK:
            sprites[boardElement]->setTexture(*textures[BoardElementType::TEXT_ROCK]);
            break;
        case BoardElementType::TEXT_IS:
            sprites[boardElement]->setTexture(*textures[BoardElementType::TEXT_IS]);
            break;
        case BoardElementType::TEXT_PUSH:
            sprites[boardElement]->setTexture(*textures[BoardElementType::TEXT_PUSH]);
            break;
        case BoardElementType::TEXT_YOU:
            sprites[boardElement]->setTexture(*textures[BoardElementType::TEXT_YOU]);
            break;
        case BoardElementType::TEXT_STOP:
            sprites[boardElement]->setTexture(*textures[BoardElementType::TEXT_STOP]);
            break;
        case BoardElementType::TEXT_WIN:
            sprites[boardElement]->setTexture(*textures[BoardElementType::TEXT_WIN]);
            break;
    }
    sprites[boardElement]->setPosition(xScreen, yScreen);
    sprites[boardElement]->setScale(s, s);
    sprites[boardElement]->setTextureRect(sf::IntRect(1, 1, 24, 24));
}

float View::calculateSpritesScale()
{
    int width{model.getBoardWidth()}, height{model.getBoardHeight()};
    float s;
    s = (height < width) ? (800.f / (24.f * (float)width)) : (800.f / (24.f * (float)height));
    return s;
}

int View::convertXGridToXScreen(int xGrid)
{
    float s = this->calculateSpritesScale();
    return (int)(24.f * s * (float)(xGrid));
}

int View::convertYGridToYScreen(int yGrid)
{
    float s = this->calculateSpritesScale();
    return (int)(24.f * s * (float)(yGrid));
}
