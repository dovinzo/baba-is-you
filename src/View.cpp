#include "View.hpp"
#include "Model.hpp"
#include "Board_elements.hpp"
#include "Enums.hpp"
#include <unordered_map>

View::View(Model& model, sf::RenderWindow& window) : textures{}, sprites{}
{
    // Création des textures
    // baba
    textures["BABA"] = new sf::Texture{};
    textures["BABA"]->loadFromFile("assets/baba.png");
    // rock
    textures["ROCK"] = new sf::Texture{};
    textures["ROCK"]->loadFromFile("assets/rock.png");
    // flag
    textures["FLAG"] = new sf::Texture{};
    textures["FLAG"]->loadFromFile("assets/flag.png");
    // wall
    textures["WALL"] = new sf::Texture{};
    textures["WALL"]->loadFromFile("assets/wall.png");
    // text is
    textures["TEXT_IS"] = new sf::Texture{};
    textures["TEXT_IS"]->loadFromFile("assets/text_is.png");
    // text baba
    textures["TEXT_BABA"] = new sf::Texture{};
    textures["TEXT_BABA"]->loadFromFile("assets/text_baba.png");
    // text you
    textures["TEXT_YOU"] = new sf::Texture{};
    textures["TEXT_YOU"]->loadFromFile("assets/text_you.png");
    // text wall
    textures["TEXT_WALL"] = new sf::Texture{};
    textures["TEXT_WALL"]->loadFromFile("assets/text_wall.png");
    // text push
    textures["TEXT_PUSH"] = new sf::Texture{};
    textures["TEXT_PUSH"]->loadFromFile("assets/text_push.png");

    // Création des sprites
    meaningful_board_element* m{nullptr};
    physical_board_element* p{nullptr};
    physical_type type{};
    meaningful_type type_m{};
    int id{};
    int h{};
    int w{};
    int x{};
    int y{};
    float s{};
    
    h = model.getGridHeight();
    w = model.getGridWidth();
    s = (h < w) ? (800.f / (24.f * (float)w)) : (800.f / (24.f * (float)h));
    for (int i = 0 ; i < model.board.current_config.size() ; i++)
    {
        for (int j = 0 ; j < model.board.current_config[i].size() ; j++)
        {
            x = (int)(24.f * s * (float)(i));
            y = (int)(24.f * s * (float)(j));
            for (Board_elements* elem : model.board.current_config[i][j])
            {
                id = elem->id;
                sprites[id] = new sf::Sprite{};
                m = dynamic_cast<meaningful_board_element*>(elem);
                p = dynamic_cast<physical_board_element*>(elem);
                if (p != nullptr)
                {
                    type = p->get_type();
                    if (type == physical_type::BABA)
                    {
                        sprites[id]->setTexture(*textures["BABA"]);
                    }
                    else if (type == physical_type::FLAG)
                    {
                        sprites[id]->setTexture(*textures["FLAG"]);
                    }
                    else if (type == physical_type::ROCK)
                    {
                        sprites[id]->setTexture(*textures["ROCK"]);
                    }
                    else if (type == physical_type::WALL)
                    {
                        sprites[id]->setTexture(*textures["WALL"]);
                    }
                }
                else
                {
                    type_m = m->get_type();
                    if (type_m == meaningful_type::IS)
                    {
                        sprites[id]->setTexture(*textures["TEXT_IS"]);
                    }
                    else if (type_m == meaningful_type::BABA)
                    {
                        sprites[id]->setTexture(*textures["TEXT_BABA"]);
                    }
                    else if (type_m == meaningful_type::YOU)
                    {
                        sprites[id]->setTexture(*textures["TEXT_YOU"]);
                    }
                    else if (type_m == meaningful_type::WALL)
                    {
                        sprites[id]->setTexture(*textures["TEXT_WALL"]);
                    }
                    else if (type_m == meaningful_type::PUSH)
                    {
                        sprites[id]->setTexture(*textures["TEXT_PUSH"]);
                    }
                }
                sprites[id]->setPosition(x, y);
                sprites[id]->setScale(s, s);
                sprites[id]->setTextureRect(sf::IntRect(1, 1, 24, 24));
            }
        }
    }
}

View::~View()
{
    std::unordered_map<std::string, sf::Texture*>::iterator it_textures = textures.begin();
    while (it_textures != textures.end())
    {
        delete it_textures->second;
        it_textures = textures.erase(it_textures);
    }

    std::unordered_map<int, sf::Sprite*>::iterator it_sprites = sprites.begin();
    while (it_sprites != sprites.end())
    {
        delete it_sprites->second;
        it_sprites = sprites.erase(it_sprites);
    }
}

void View::update(Model& model)
{
    int id{};
    int h{};
    int w{};
    int x{};
    int y{};
    float s{};

    h = model.getGridHeight();
    w = model.getGridWidth();
    s = (h < w) ? (800.f / (24.f * (float)w)) : (800.f / (24.f * (float)h));

    for (int i = 0 ; i < model.board.current_config.size() ; i++)
    {
        for (int j = 0 ; j < model.board.current_config[i].size() ; j++)
        {
            x = (int)(24.f * s * (float)(i));
            y = (int)(24.f * s * (float)(j));
            for (Board_elements* elem : model.board.current_config[i][j])
            {
                id = elem->id;
                sprites[id]->setPosition(x, y);
            }
        }
    }
}

void View::draw(sf::RenderWindow& window)
{
    std::unordered_map<int, sf::Sprite*>::iterator it_sprites = sprites.begin();
    while (it_sprites != sprites.end())
    {
        window.draw(*(it_sprites->second));
        it_sprites++;
    }
}
