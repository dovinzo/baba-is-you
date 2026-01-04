#include "BoardElement.hpp"
#include "Enums.hpp"
#include "Rules.hpp"
#include "Model.hpp"

BoardElement::BoardElement(BoardElementType type, int x, int y): type{type}, x{x}, y{y}
{
}

BoardElementType BoardElement::getType() const
{
    return type;
}

BoardElementCategory BoardElement::getCategory() const
{
    BoardElementCategory boardElementCategory{};
    switch (type)
    {
        case BoardElementType::BABA:
        case BoardElementType::WALL:
        case BoardElementType::FLAG:
        case BoardElementType::ROCK:
        case BoardElementType::WATER:
            boardElementCategory = BoardElementCategory::OBJECT;
            break;
        case BoardElementType::TEXT_BABA:
        case BoardElementType::TEXT_WALL:
        case BoardElementType::TEXT_FLAG:
        case BoardElementType::TEXT_ROCK:
        case BoardElementType::TEXT_WATER:
            boardElementCategory = BoardElementCategory::TEXT_OBJECT;
            break;
        case BoardElementType::TEXT_IS:
            boardElementCategory = BoardElementCategory::TEXT_IS;
            break;
        default:
            boardElementCategory = BoardElementCategory::TEXT_PROPERTY;
            break;
    }
    return boardElementCategory;
}

BoardElementType BoardElement::intToBoardElementType(int typeCode)
{
    BoardElementType boardElementType{};
    switch (typeCode)
    {
        case 0:
            boardElementType = BoardElementType::BABA;
            break;
        case 1:
            boardElementType = BoardElementType::WALL;
            break;
        case 2:
            boardElementType = BoardElementType::FLAG;
            break;
        case 3:
            boardElementType = BoardElementType::ROCK;
            break;
        case 4:
            boardElementType = BoardElementType::TEXT_BABA;
            break;
        case 5:
            boardElementType = BoardElementType::TEXT_WALL;
            break;
        case 6:
            boardElementType = BoardElementType::TEXT_FLAG;
            break;
        case 7:
            boardElementType = BoardElementType::TEXT_ROCK;
            break;
        case 8:
            boardElementType = BoardElementType::TEXT_IS;
            break;
        case 9:
            boardElementType = BoardElementType::TEXT_PUSH;
            break;
        case 10:
            boardElementType = BoardElementType::TEXT_YOU;
            break;
        case 11:
            boardElementType = BoardElementType::TEXT_STOP;
            break;
        case 12:
            boardElementType = BoardElementType::TEXT_WIN;
            break;
        case 13:
            boardElementType = BoardElementType::TEXT_WATER;
            break;
        case 14:
            boardElementType = BoardElementType::TEXT_SINK;
            break;
        case 15:
            boardElementType = BoardElementType::WATER;
            break;    
        default: return BoardElementType::INVALID;
        
    }
    return boardElementType;
}

int BoardElement::getPositionX() const
{
    return x;
}

int BoardElement::getPositionY() const
{
    return y;
}

void BoardElement::setPositionX(int x)
{
    this->x = x;
}

void BoardElement::setPositionY(int y)
{
    this->y = y;
}
