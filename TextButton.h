#ifndef TEXTBUTTON_H_INCLUDED
#define TEXTBUTTON_H_INCLUDED

#include <SFML/OpenGL.hpp>
#include "Widget.h"
#include <string>
#include <iostream>




namespace gui
{
    class TextButton : public Widget
    {

    private:
        sf::Vector2f _position;
        std::string str;
        unsigned int strSize;
        sf::Font _font;
        sf::Text _text;
        sf::Text _selectionText;
        sf::RectangleShape _cursor;
        sf::RectangleShape _buttonBox;
        size_t _cursorPos;
        bool select;
        float offset;
        int _status;
        sf::RectangleShape _selection;
        size_t _selectionPos;
        sf::Clock clock;
        sf::Cursor cursor;

        enum Status
        {
            None=0,
            Activ
        };


    public:

        TextButton(sf::Vector2f position = sf::Vector2f(0,0),
               unsigned int x=200,unsigned int y=60, Widget* parent=nullptr);

        void updateShape();
        void setText(sf::Uint32 unicode);
        void enterText(sf::Uint32 unicode);
        void setCursor(size_t index);
        void setSelection();
        void setCursorBlink();
        void selectionDrop();
        void selectionDelete();
        void onPressKey(const sf::Event::KeyEvent& key);
        void mouseCursorPos(float x, float y);
        void mouseSelection(float x, float y);
        sf::Cursor& setCursorSkin(float x, float y);
        void onMousePressed(float x, float y);
        virtual void processEvent(sf::Event& event)override;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
    };
}


#endif // TEXTBUTTON_H_INCLUDED
