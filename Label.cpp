
#include "Label.h"

namespace gui
{

    Label::Label(const std::string& text, unsigned int charSize,
          sf::Vector2f position, Widget* parent): _position(position),Widget(parent)
    {
        setText(text);
        setFont("18028.ttf");
        setCharSize(charSize);
        setColor(sf::Color::Black);
        _text.setStyle(0);
    }

    Label::~Label(){}

    void Label::setText(const std::string& text)
    {
        str=text;
        _text.setString(str);
    }

    const sf::Text& Label::getText()const
    {
        return _text;
    }

    void Label::setCharSize(unsigned int& size)
    {
        _charSize=size;
        _text.setCharacterSize(_charSize);
    }

    unsigned int& Label::getCharSize()
    {
        return _charSize;
    }

    void Label::setFont(const std::string& font)
    {
        _font.loadFromFile(font);
        _text.setFont(_font);
    }

    sf::Font& Label::getFont()
    {
        return _font;
    }

    void Label::setColor(const sf::Color& color)
    {
        _color=color;
        _text.setColor(_color);
    }

    sf::Color& Label::getColor()
    {
        return _color;
    }

    void Label::setPosition(sf::Vector2f& position)
    {
        _position=position;
    }

    void Label::setPosition(float x, float y)
    {
        _position.x=x;
        _position.y=y;
    }

    const sf::Vector2f& Label::getPosition()const
    {
        return _position;
    }

    sf::Vector2f Label::getSize()
    {
        sf::FloatRect rect = _text.getLocalBounds();
        return sf::Vector2f(rect.width,rect.height);
    }

    void Label::draw(sf::RenderTarget& target, sf::RenderStates states)const
    {
        states.transform.translate(_position);
        target.draw(_text,states);
    }

    sf::Text& Label::redText()
    {
        return _text;
    }

}
