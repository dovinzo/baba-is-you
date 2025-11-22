#include "Model.hpp"
#include "ObjectType.hpp"
#include "IObserver.hpp"
#include <list>

Model::Model(int width, int height) : width{width}, height{height}, grid{nullptr}, observers{}
{
    grid = new std::list<ObjectType>*[width]{nullptr};
    for (int x = 0 ; x < width ; x++)
    {
        grid[x] = new std::list<ObjectType>[height]{};
    }
}

Model::~Model()
{
    for (int x = 0 ; x < width ; x++)
    {
        delete[] grid[x];
    }
    delete[] grid;
}

int Model::getWidth() const
{
    return width;
}

int Model::getHeight() const
{
    return height;
}

const std::list<ObjectType>& Model::cell(int x, int y) const
{
    return grid[x][y];
}

void Model::attach(IObserver *observer)
{
    observers.push_back(observer);
}

void Model::detach(IObserver *observer)
{
    observers.remove(observer);
}

void Model::notify()
{
    std::list<IObserver*>::iterator iterator = observers.begin();
    while (iterator != observers.end())
    {
        (*iterator)->update();
        iterator++;
    }
}