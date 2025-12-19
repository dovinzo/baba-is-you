#include "View.hpp"
#include "Model.hpp"
#include "BoardElement.hpp"
#include "Enums.hpp"
#include <unordered_map>

View::View(Model& model, sf::RenderWindow& window) : textures{}, sprites{}
{
    this->createTextures();
    this->createSprites(model, window);
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

void View::update(Model& model)
{
    int width{model.board.getWidth()};
    int height{model.board.getHeight()};
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
            for (int i = 0 ; i < static_cast<int>(model.board.grid[x][y].size()) ; i++)
            {
                sprites[model.board.grid[x][y][i]]->setPosition(xScreen, yScreen);
            }
        }
    }
}

// ENCOURS
void View::draw(sf::RenderWindow& window, Model& model)
{
    for (int x = 0 ; x < model.board.getWidth() ; x++)
    {
        for (int y = 0 ; y < model.board.getHeight() ; y++)
        {
            for (int i = 0 ; i < static_cast<int>(model.board.grid[x][y].size()) ; i++)
            {
                window.draw(*sprites[model.board.grid[x][y][i]]);
            }
        }
    }
    //std::unordered_map<BoardElement*, sf::Sprite*>::iterator it_sprites = sprites.begin();
    //while (it_sprites != sprites.end())
    //{
        //window.draw(*(it_sprites->second));
        //it_sprites++;
    //}
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
}

void View::createSprites(Model& model, sf::RenderWindow& window)
{
    int width{model.board.getWidth()}, height{model.board.getHeight()};
    for (int x = 0 ; x < width ; x++)
    {
        for (int y = 0 ; y < height ; y++)
        {
            for (int i = 0 ; i < static_cast<int>(model.board.grid[x][y].size()) ; i++)
            {
                this->createSprite(model.board.grid[x][y][i], model);
            }
        }
    }
}

void View::createSprite(BoardElement* boardElement, Model& model)
{
    int xGrid{boardElement->getPositionX()}, yGrid{boardElement->getPositionY()};
    int xScreen{View::convertXGridToXScreen(model, xGrid)}, yScreen{View::convertYGridToYScreen(model, yGrid)};
    float s{View::calculateSpritesScale(model)};
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

float View::calculateSpritesScale(Model& model)
{
    int width{model.board.getWidth()}, height{model.board.getHeight()};
    float s;
    s = (height < width) ? (800.f / (24.f * (float)width)) : (800.f / (24.f * (float)height));
    return s;
}

int View::convertXGridToXScreen(Model& model, int xGrid)
{
    float s = View::calculateSpritesScale(model);
    return (int)(24.f * s * (float)(xGrid));
}

int View::convertYGridToYScreen(Model& model, int yGrid)
{
    float s = View::calculateSpritesScale(model);
    return (int)(24.f * s * (float)(yGrid));
}
