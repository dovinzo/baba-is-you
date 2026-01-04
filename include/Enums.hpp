#ifndef ENUMS_HPP
#define ENUMS_HPP

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
    INVALID
};

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

enum class MenuItem
{
    LEVEL1,
    LEVEL2,
    LEVEL3
};

#endif