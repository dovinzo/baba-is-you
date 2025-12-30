#ifndef BOARDELEMENT_HPP
#define BOARDELEMENT_HPP

#include "Enums.hpp"
#include "Rules.hpp"

class Board;
class BoardSnapshot;


class BoardElement
{
    public:
        BoardElement() = delete;
        BoardElement(const BoardElement& boardElement) = delete;
        ~BoardElement() = default;
        BoardElement& operator=(const BoardElement& boardElement) = delete;
        BoardElementCategory getCategory() const;
        BoardElementType getType() const;
        int getPositionX() const;
        int getPositionY() const;


        friend class Board;
        friend class BoardSnapshot;
    private:
        //static int idCounter;
        BoardElement(BoardElementType type, int x, int y);

        static BoardElementType intToBoardElementType(int typeCode);
        void setPositionX(int x);
        void setPositionY(int y);

        BoardElementType type;
        int x;
        int y;
};

#endif
