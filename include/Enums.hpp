#ifndef ENUMS_HPP
#define ENUMS_HPP

/* Typage fort des différents éléments du jeu. */

enum class BoardElementType
{
    BABA,
    WALL,
    FLAG,
    ROCK,
    WATER,
    TEXT_BABA,
    TEXT_WALL,
    TEXT_FLAG,
    TEXT_ROCK,
    TEXT_IS,
    TEXT_PUSH,
    TEXT_YOU,
    TEXT_STOP,
    TEXT_WIN,
    TEXT_WATER,
    TEXT_SINK,
    INVALID // permet de gérer les exceptions.
};

// Une rule est un élément de type 'Object' + IS + 'Property'.
/* Si cette implémentation à le mérite d'éviter de gérer tous les cas possibles en
imposant une grammaire claire, elle manque aussi de développement possible.
Gérer les Baba is Wall, par exemple, sera compliqué.  */
enum class BoardElementCategory
{
    OBJECT,
    TEXT_OBJECT,
    TEXT_IS,
    TEXT_PROPERTY
};

enum class Direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

enum class RuleSubject
{
    BABA,
    WALL,
    FLAG,
    ROCK,
    WATER
};

enum class RuleProperty
{
    BABA,
    WALL,
    FLAG,
    ROCK,
    PUSH,
    YOU,
    STOP,
    WIN,
    SINK,
    WATER
};

enum class AppState
{
    MENU,
    LEVEL,
    QUIT
};

// Une autre implémentation, qui viendrait compter le nombre de fichier .txt dans les src
// serait préférable.
enum class MenuItem
{
    LEVEL1,
    LEVEL2,
    LEVEL3
};

#endif
