#include "View.hpp"
#include "Model.hpp"
#include "BoardElement.hpp"
#include "Enums.hpp"
#include <unordered_map>

View::View(Model& model, sf::RenderWindow& window) : textures{}, model{model}, window{window}
{
    this->createTextures();
}

View::~View()
{
    std::unordered_map<BoardElementType, sf::Texture*>::iterator it_textures = textures.begin();
    while (it_textures != textures.end())
    {
        delete it_textures->second;
        it_textures = textures.erase(it_textures);
    }
}

void View::draw()
{
    sf::Sprite sprite;
    std::vector<BoardElement*> cell;
    for (int x = 0 ; x < model.getBoardWidth() ; x++)
    {
        for (int y = 0 ; y < model.getBoardHeight() ; y++)
        {
            cell = model.getBoardCell(x, y);
            for (int i = 0 ; i < static_cast<int>(cell.size()) ; i++)
            {
                this->updateSpriteFromBoardElement(sprite, *cell[i]);
                window.draw(sprite);
            }
        }
    }
}

sf::Texture* loadTexture(const std::string path) {
    sf::Texture* tex = new sf::Texture{};
    if (!tex->loadFromFile(path)) {
        delete tex;
        throw std::runtime_error("Problème avec la texture " + path);
    }
    return tex;
}

void View::createTextures()
{
    textures[BoardElementType::BABA] = loadTexture("assets/baba.png");
    textures[BoardElementType::ROCK] = loadTexture("assets/rock.png");
    textures[BoardElementType::FLAG] = loadTexture("assets/flag.png");
    textures[BoardElementType::WALL] = loadTexture("assets/wall.png");
    textures[BoardElementType::WATER] = loadTexture("assets/water.png");
    textures[BoardElementType::TEXT_IS] = loadTexture("assets/text_is.png");
    textures[BoardElementType::TEXT_BABA] = loadTexture("assets/text_baba.png");
    textures[BoardElementType::TEXT_YOU] = loadTexture("assets/text_you.png");
    textures[BoardElementType::TEXT_WALL] = loadTexture("assets/text_wall.png");
    textures[BoardElementType::TEXT_PUSH] = loadTexture("assets/text_push.png");
    textures[BoardElementType::TEXT_FLAG] = loadTexture("assets/text_flag.png");
    textures[BoardElementType::TEXT_WIN] = loadTexture("assets/text_win.png");
    textures[BoardElementType::TEXT_ROCK] = loadTexture("assets/text_rock.png");
    textures[BoardElementType::TEXT_STOP] = loadTexture("assets/text_stop.png");
    textures[BoardElementType::TEXT_WATER] = loadTexture("assets/text_water.png");
    textures[BoardElementType::TEXT_SINK] = loadTexture("assets/text_sink.png");
    textures[BoardElementType::INVALID] = nullptr;
}

void View::updateSpriteFromBoardElement(sf::Sprite& sprite, BoardElement& boardElement)
{
    int xGrid{boardElement.getPositionX()}, yGrid{boardElement.getPositionY()};
    int xScreen{View::convertXGridToXScreen(xGrid)}, yScreen{View::convertYGridToYScreen(yGrid)};
    float s{View::calculateSpritesScale()};

    switch (boardElement.getType())
    {
        case BoardElementType::BABA:
            sprite.setTexture(*textures[BoardElementType::BABA]);
            break;
        case BoardElementType::WALL:
            sprite.setTexture(*textures[BoardElementType::WALL]);
            break;
        case BoardElementType::FLAG:
            sprite.setTexture(*textures[BoardElementType::FLAG]);
            break;
        case BoardElementType::ROCK:
            sprite.setTexture(*textures[BoardElementType::ROCK]);
            break;
        case BoardElementType::WATER:
            sprite.setTexture(*textures[BoardElementType::WATER]);
            break;
        case BoardElementType::TEXT_BABA:
            sprite.setTexture(*textures[BoardElementType::TEXT_BABA]);
            break;
        case BoardElementType::TEXT_WALL:
            sprite.setTexture(*textures[BoardElementType::TEXT_WALL]);
            break;
        case BoardElementType::TEXT_FLAG:
            sprite.setTexture(*textures[BoardElementType::TEXT_FLAG]);
            break;
        case BoardElementType::TEXT_ROCK:
            sprite.setTexture(*textures[BoardElementType::TEXT_ROCK]);
            break;
        case BoardElementType::TEXT_IS:
            sprite.setTexture(*textures[BoardElementType::TEXT_IS]);
            break;
        case BoardElementType::TEXT_PUSH:
            sprite.setTexture(*textures[BoardElementType::TEXT_PUSH]);
            break;
        case BoardElementType::TEXT_YOU:
            sprite.setTexture(*textures[BoardElementType::TEXT_YOU]);
            break;
        case BoardElementType::TEXT_STOP:
            sprite.setTexture(*textures[BoardElementType::TEXT_STOP]);
            break;
        case BoardElementType::TEXT_WIN:
            sprite.setTexture(*textures[BoardElementType::TEXT_WIN]);
            break;
        case BoardElementType::TEXT_WATER:
            sprite.setTexture(*textures[BoardElementType::TEXT_WATER]);
            break;
        case BoardElementType::TEXT_SINK:
            sprite.setTexture(*textures[BoardElementType::TEXT_SINK]);
            break;
        case BoardElementType::INVALID:
            throw std::runtime_error("View::updateSpriteFromBoardElement: boardElement de type INVALID");
    }
    sprite.setPosition(xScreen, yScreen);
    sprite.setScale(s, s);
    sprite.setTextureRect(sf::IntRect(1, 1, 24, 24));
}

float View::calculateSpritesScale() {
    auto size = window.getSize();
    float cellPx = 24.f;
    float scaleX = static_cast<float>(size.x) / (cellPx * model.getBoardWidth());
    float scaleY = static_cast<float>(size.y) / (cellPx * model.getBoardHeight());
    return std::min(scaleX, scaleY);
}

int View::convertXGridToXScreen(int xGrid) {
    float s = calculateSpritesScale();
    float boardPx = 24.f * s * model.getBoardWidth();
    float offset = (window.getSize().x - boardPx) * 0.5f;
    return static_cast<int>(offset + 24.f * s * xGrid);
}

int View::convertYGridToYScreen(int yGrid) {
    float s = calculateSpritesScale();
    float boardPx = 24.f * s * model.getBoardHeight();
    float offset = (window.getSize().y - boardPx) * 0.5f;
    return static_cast<int>(offset + 24.f * s * yGrid);
}

