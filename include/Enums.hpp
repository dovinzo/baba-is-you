#ifndef ENUMS_HPP
#define ENUMS_HPP

enum class BoardElementType
{
    BABA,
    WALL,
    FLAG,
    ROCK,
    TEXT_BABA,
    TEXT_WALL,
    TEXT_FLAG,
    TEXT_ROCK,
    TEXT_IS,
    TEXT_PUSH,
    TEXT_YOU,
    TEXT_STOP,
    TEXT_WIN
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
    ROCK
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
    WIN
};

#endif
