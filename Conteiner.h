#ifndef CONTEINER_H_INCLUDED
#define CONTEINER_H_INCLUDED

#include "Widget.h"
#include <vector>


namespace gui
{

    class Conteiner : public Widget
    {
    private:

        sf::Vector2f _conteinerPosition;
        sf::Vector2f _conteinerSize;
        float _space;
        std::vector<Widget*> _widgets;

    public:

        Conteiner(Widget* parent = nullptr);

        ~Conteiner();

        void setSpace(float space);

        float& getSpace();

        void setConteinerSize(sf::Vector2f& conteinerSize);

        const sf::Vector2f& getConteinerSize()const;

        void setConteinerPosition(sf::Vector2f& conteinerPosition);

        const sf::Vector2f getConteinerPosition()const;

        void addWidget(Widget* widget);


        Widget* indexerWidgets(unsigned int i);

        virtual void updateShape();

        virtual void processEvent(sf::Event& event)override;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override;

    };
}


#endif // CONTEINER_H_INCLUDED
