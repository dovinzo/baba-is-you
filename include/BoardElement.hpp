#ifndef BOARDELEMENT_HPP
#define BOARDELEMENT_HPP

#include "Enums.hpp"
#include "Rules.hpp"

class BoardElement
{
    public:
        BoardElement() = delete;
        BoardElement(BoardElementType type, int x, int y);
        BoardElement(const BoardElement& boardElement) = delete;
        BoardElement& operator=(const BoardElement& boardElement) = delete;
        BoardElementCategory getCategory() const;
        BoardElementType getType() const;
        int getPositionX() const;
        int getPositionY() const;
        void setPositionX(int x);
        void setPositionY(int y);
        static BoardElementType intToBoardElementType(int typeCode);
    private:
        //static int idCounter;
        //const int id; Son adresse est déjà un id
        BoardElementType type;
        int x;
        int y;
};

#endif
