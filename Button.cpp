#include "Button.h"

namespace gui
{

        Button::Button(const std::string& text, sf::Vector2f position,
               unsigned int x,unsigned int y, Widget* parent):_status(Status::None), Widget(parent)
        {
            setText(text);
            setButtonColor(sf::Color::White);
            setButtonSize(x,y);
            setEdgeColor(sf::Color::Black);
            setEdgeSize(2);
            setPosition(position);
            updateShape();
            res = false;
        }

        Button::~Button(){}

        void Button::setPosition(sf::Vector2f& position)
        {
            _position=position;
            _position.x+=_edgeSize;
            _position.y+=_edgeSize;
        }

        void Button::setPosition(float x, float y)
        {
            _position.x=x+_edgeSize;
            _position.y=y+_edgeSize;
        }

        sf::Vector2f Button::getPosition()
        {
            return _position;
        }

        void Button::setText(const std::string& text)
        {
            _label.setText(text);
        }

        void Button::setTexture(const sf::Texture& picture)
        {
            _shape.setTexture(&picture);
        }

        void Button::setButtonColor(const sf::Color& color)
        {
            _buttonColor=color;
            _shape.setFillColor(_buttonColor);
        }

        void Button::setEdgeColor(const sf::Color& color)
        {
            _edgeColor=color;
            _shape.setOutlineColor(_edgeColor);
        }

        void Button::setEdgeSize(unsigned int edgeSize)
        {
            _edgeSize=edgeSize;
            _shape.setOutlineThickness(_edgeSize);
        }

        void Button::setButtonSize(const sf::Vector2f& buttonSize)
        {
            _buttonSize=buttonSize;
            _shape.setSize(_buttonSize);
        }

        void Button::setButtonSize(float x, float y)
        {
            _buttonSize.x=x;
            _buttonSize.y=y;
            _shape.setSize(_buttonSize);
        }

        sf::Vector2f& Button::getButtonSize()
        {
            return _buttonSize;
        }

        void Button::updateShape()
        {
            if(_label.getText().getString()!="")
            {
                sf::Vector2f label_size = _label.getSize();
                unsigned int char_size = _label.getCharSize();
                _shape.setSize(sf::Vector2f(char_size*2 + _buttonSize.x*2 + label_size.x ,char_size*2 + _buttonSize.y*2 + label_size.y));
                _label.setPosition(char_size + _buttonSize.x, char_size + _buttonSize.y);
                _buttonSize=_shape.getSize();
            }
        }

       void Button::processEvent(sf::Event& event)
       {

            if(event.type == sf::Event::MouseButtonReleased)
            {
                /*const sf::Vector2f pos = _position;
                const sf::Vector2f size = getButtonSize();
                sf::FloatRect rect;

                rect.left = pos.x;
                rect.top = pos.y;
                rect.width = size.x+_edgeSize;
                rect.height = size.y+_edgeSize;*/
                if(res)
                {onClick();
                res=false;
                }
            }
            else if(event.type == sf::Event::MouseButtonPressed)
            {
                const sf::Vector2f pos = _position;
                const sf::Vector2f size = getButtonSize();
                sf::FloatRect rect;

                rect.left = pos.x;
                rect.top = pos.y;
                rect.width = size.x+_edgeSize;
                rect.height = size.y+_edgeSize;

                if(rect.contains(event.mouseButton.x,event.mouseButton.y))
                {

                    onMousePress();
                    res=true;
                }

            }
            else if (event.type == sf::Event::MouseMoved)
            {
                const sf::Vector2f pos = _position;
                const sf::Vector2f size = getButtonSize();
                sf::FloatRect rect;

                rect.left = pos.x;
                rect.top = pos.y;
                rect.width = size.x+_edgeSize;
                rect.height = size.y+_edgeSize;

                int old_status = _status;
                _status = Status::None;
                const sf::Vector2f mouse_pos(event.mouseMove.x,event.mouseMove.y);
                if(rect.contains(mouse_pos))
                {
                    _status|=Status::Activ;
                }

                if((old_status & Status::Activ) and not (_status & Status::Activ))
                    {
                        if(!res)
                            onMouseLeft();

                    }
                else if(not (old_status & Status::Activ) and (_status & Status::Activ))
                    onMouseEntered();
            }
        }


       void Button::onMouseEntered()
       {
            _shape.setOutlineColor(sf::Color(200,0,0));
            _shape.setFillColor(sf::Color(20,150,20));
       }

       void Button::onMouseLeft()
       {
            _shape.setOutlineColor(_edgeColor);
            _shape.setFillColor(_buttonColor);
       }

       void Button::onMousePress()
       {
           _shape.setOutlineColor(sf::Color(0,0,0));
           _shape.setFillColor(sf::Color(250,0,100));
       }

       void Button::onClick()
       {
           _shape.setOutlineColor(sf::Color(50,120,50));
           _shape.setFillColor(sf::Color(200,80,0));

       }

       void Button::draw(sf::RenderTarget& target, sf::RenderStates states)const
       {
           if(_label.getText().getString()=="")
           {
                states.transform.translate(_position);
                target.draw(_shape,states);
           }
           else
           {
               states.transform.translate(_position);
               target.draw(_shape,states);
               target.draw(_label,states);
           }
       }
}
