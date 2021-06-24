#include "Conteiner.h"
#include <iostream>


namespace gui
{

        Conteiner::Conteiner(Widget* parent) : Widget(parent)
        {

        }

        Conteiner::~Conteiner()
        {
            for(auto widget : _widgets)
            {
                delete widget;
            }
         _widgets.clear();
         _widgets.shrink_to_fit();
        }

        void Conteiner::setSpace(float space)
        {
            _space=space;
        }

        float& Conteiner::getSpace()
        {
            return _space;
        }

        void Conteiner::setConteinerSize(sf::Vector2f& conteinerSize)
        {
            _conteinerSize=_conteinerSize;
        }

        const sf::Vector2f& Conteiner::getConteinerSize()const
        {
            return _conteinerSize;
        }

        void Conteiner::setConteinerPosition(sf::Vector2f& conteinerPosition)
        {
            _conteinerPosition=conteinerPosition;
        }

        const sf::Vector2f Conteiner::getConteinerPosition()const
        {
            return _conteinerPosition;
        }

        void Conteiner::addWidget(Widget* widget)
        {
            _widgets.emplace_back(widget);
        }


        Widget* Conteiner::indexerWidgets(unsigned int i)
        {
            return _widgets.at(i);
        }

        void Conteiner::updateShape()
        {

        }

        void Conteiner::processEvent(sf::Event& event)
        {
            for(auto widget : _widgets)
            {
                widget->processEvent(event);
            }
        }

        void Conteiner::draw(sf::RenderTarget& target, sf::RenderStates states)const
        {
            for(auto widget : _widgets)
            {
                target.draw(*widget,states);
            }
        }
}
