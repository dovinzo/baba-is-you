#ifndef MODEL_HPP
#define MODEL_HPP

#include "IReadOnlyModel.hpp"
#include "ObjectType.hpp"
#include "ISubject.hpp"
#include "IObserver.hpp"
#include <list>

class Model : public IReadOnlyModel, ISubject
{
    public:
        Model() = delete;
        Model(int width, int height);
        virtual ~Model();
        virtual int getWidth() const override;
        virtual int getHeight() const override;
        virtual const std::list<ObjectType>& cell(int x, int y) const override;
        virtual void attach(IObserver *observer) override;
        virtual void detach(IObserver *observer) override;
        virtual void notify() override;
    private:
        int width;
        int height;
    public: // temporaire !!
        std::list<ObjectType>** grid;
        std::list<IObserver*> observers;
};

#endif