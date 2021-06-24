#ifndef WIDGET_H_INCLUDED
#define WIDGET_H_INCLUDED

#include<SFML/Graphics.hpp>

namespace gui
{
    class Widget : public sf::Drawable
    {
    public:
        Widget* _parent;
        Widget(Widget* parent= nullptr);
        virtual ~Widget();
        virtual void processEvent(sf::Event& event);
    };
}

#endif // WIDGET_H_INCLUDED
