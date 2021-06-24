#include "Widget.h"

namespace gui
{
    Widget::Widget(Widget* parent):_parent(parent)
    {

    }

    void Widget::processEvent(sf::Event& event){}
    Widget::~Widget(){}
}
