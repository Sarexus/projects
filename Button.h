#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "Label.h"


namespace gui
{
    class Button : public Widget
    {

    protected:
        Label _label;
        sf::Vector2f _position;
        sf::Color _buttonColor;
        sf::Color _edgeColor;
        unsigned int _edgeSize;
        sf::Vector2f _buttonSize;
        sf::RectangleShape _shape;

        bool res;



    public:
        int _status;
        enum Status
        {
            None=0,
            Activ
        };
        Button(const std::string& text="button", sf::Vector2f position = sf::Vector2f(0,0),
               unsigned int x=5,unsigned int y=3, Widget* parent = nullptr);
        ~Button();

        void setPosition(sf::Vector2f& position);

        void setPosition(float x, float y);

        sf::Vector2f getPosition();

        void setText(const std::string& text);

        void setTexture(const sf::Texture& picture);

        void setButtonColor(const sf::Color& color);

        void setEdgeColor(const sf::Color& color);

        void setEdgeSize(unsigned int edgeSize);

        void setButtonSize(const sf::Vector2f& buttonSize);

        void setButtonSize(float x, float y);

        sf::Vector2f& getButtonSize();

        virtual void updateShape();
        virtual void processEvent(sf::Event& event)override;

        void onMouseEntered();
        void onMouseLeft();
        virtual void onClick();
        void onMousePress();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override;

    };
}
#endif // BUTTON_H_INCLUDED
