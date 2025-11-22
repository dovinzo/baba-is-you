#ifndef IREADONLYMODEL_HPP
#define IREADONLYMODEL_HPP

#include "ObjectType.hpp"
#include <list>

class IReadOnlyModel
{
    public:
        virtual ~IReadOnlyModel() = default;
        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;
        virtual const std::list<ObjectType>& cell(int x, int y) const = 0;
};

#endif