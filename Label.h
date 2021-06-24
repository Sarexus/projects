#ifndef LABEL_H_INCLUDED
#define LABEL_H_INCLUDED
#include "Widget.h"


namespace gui
{
    class Label : public Widget
{
private:
    std::string str;
    sf::Vector2f _position;
    sf::Text _text;
    sf::Font _font;
    sf::Color _color;
    unsigned int _charSize;

public:
    Label(const std::string& text="label", unsigned int charSize = 14,
          sf::Vector2f position=sf::Vector2f(0,0), Widget* parent=nullptr);

    ~Label();

    void setText(const std::string& text);

    const sf::Text& getText()const;

    void setCharSize(unsigned int& size);

    unsigned int& getCharSize();

    void setFont(const std::string& font);

    sf::Font& getFont();

    void setColor(const sf::Color& color);

    sf::Color& getColor();

    void setPosition(sf::Vector2f& position);

    void setPosition(float x, float y);

    const sf::Vector2f& getPosition()const;

    sf::Vector2f getSize();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
    sf::Text& redText();

};
}


#endif // LABEL_H_INCLUDED
