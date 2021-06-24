#include "TextButton.h"




namespace gui
{

TextButton::TextButton(sf::Vector2f position,
               unsigned int x,unsigned int y, Widget* parent): _cursorPos(0),_selectionPos(0), Widget(parent)
        {
            _position=position;
            _font.loadFromFile("18028.ttf");
            _text.setString("");
            _selectionText.setString("");
            _text.setFont(_font);
            _selectionText.setFont(_font);
            _text.setColor(sf::Color::Black);
            _selectionText.setColor(sf::Color::White);
            _status=Status::None;
            _buttonBox.setFillColor(sf::Color::White);
            _buttonBox.setSize(sf::Vector2f(x,y));
            _buttonBox.setOutlineColor(sf::Color::Black);
            _buttonBox.setOutlineThickness(2);
            _position.x+=_buttonBox.getOutlineThickness();
            _position.y+=_buttonBox.getOutlineThickness();
            strSize = 20;
            offset = 6;
            updateShape();
            _selection.setFillColor(sf::Color(0,0,150));
        }

        void TextButton::updateShape() // Задание формы и расположения всех элементов кнопки
        {
            unsigned int chSize=_buttonBox.getSize().y/2;
            _text.setCharacterSize(chSize);
            _text.setPosition(offset,(_buttonBox.getSize().y-chSize)/2);
            _cursor.setSize(sf::Vector2f(2,(_buttonBox.getSize().y+chSize)/2));
            _cursor.setPosition(sf::Vector2f(offset,(_buttonBox.getSize().y-_cursor.getSize().y)/2));
        }

        void TextButton::setText(sf::Uint32 unicode) // Ввод текста в конец строки
        {
            if(unicode>30 && (unicode<127||unicode>159))
            {
                if(_selectionText.getString()!="")
                    {
                        selectionDelete();
                    }
                if(str.size()<strSize)
                {

                    str+=unicode;
                    _text.setString(str);
                    setCursor(str.size());
                }
            }
        }

        void TextButton::enterText(sf::Uint32 unicode) // Ввод текста с позиции курсора
        {
            if(unicode>30 && (unicode<127||unicode>159))
            {
                if(_selectionText.getString()!="")
                    {
                        selectionDelete();
                    }
                if(str.size()<strSize)
                {

                    str.insert(_cursorPos,1,unicode);
                    _text.setString(str);
                    setCursor(_cursorPos+1);
                }
            }
        }

        void TextButton::setCursor(size_t index) // Установить позицию курсора
        {
            if(index<=strSize)
            {
                _cursorPos=index;
                _selectionPos=index;
                _cursor.setPosition(_text.findCharacterPos(index).x,(_buttonBox.getSize().y-_cursor.getSize().y)/2);
            }
            if(_cursor.getPosition().x < offset)
            {
                float diff = offset - _cursor.getPosition().x;
                _text.move(diff,0);
                _cursor.move(diff,0);

            }
            else if(_cursor.getPosition().x > _buttonBox.getSize().x-offset)
            {
                float diff = _cursor.getPosition().x - _buttonBox.getSize().x+offset;
                _text.move(-diff,0);
                _cursor.move(-diff,0);
            }

            float textWidth =_text.getLocalBounds().width;
            if(_text.getPosition().x<offset && _text.getPosition().x+textWidth<_buttonBox.getSize().x-offset*2-2)
            {
                float diff=(_buttonBox.getSize().x-offset*2-2)-(_text.getPosition().x+textWidth);
                _text.move(diff,0);
                _cursor.move(diff,0);

                if(textWidth<_buttonBox.getSize().x-offset*2-2)
                {
                    diff=offset-_text.getPosition().x;
                    _text.move(diff,0);
                    _cursor.move(diff,0);
                }
            }

        }

        void TextButton::setSelection() // Создать выделение
        {
            std::string string;
            if(_cursorPos>_selectionPos)
            {
                size_t sel = _cursorPos- _selectionPos;
                string = str.substr(_selectionPos,sel);
                _selectionText.setString(string);
                _selectionText.setPosition(_text.findCharacterPos(_selectionPos).x,_text.getPosition().y);
                _selection.setPosition(_text.findCharacterPos(_selectionPos).x,_cursor.getPosition().y);
                _selection.setSize(sf::Vector2f(_text.findCharacterPos(_cursorPos).x-_text.findCharacterPos(_selectionPos).x,_cursor.getLocalBounds().height));
            }
            else
            {
                size_t sel = _selectionPos-_cursorPos;
                string = str.substr(_cursorPos,sel);
                _selectionText.setString(string);
                _selectionText.setPosition(_text.findCharacterPos(_cursorPos).x,_text.getPosition().y);
                _selection.setPosition(_text.findCharacterPos(_cursorPos).x,_cursor.getPosition().y);
                _selection.setSize(sf::Vector2f(_text.findCharacterPos(_selectionPos).x-_text.findCharacterPos(_cursorPos).x,_cursor.getLocalBounds().height));
            }

            if(_selectionText.getString()!="")
            {
                if(_text.findCharacterPos(_selectionPos-1).x<offset)
                {
                    float diff = offset - _text.findCharacterPos(_selectionPos-1).x;
                    _text.move(diff,0);
                    _selection.move(diff,0);
                    _selectionText.move(diff,0);
                }
                else if(_text.findCharacterPos(_selectionPos+1).x>_buttonBox.getSize().x-offset)
                {
                    float diff = _text.findCharacterPos(_selectionPos+1).x-(_buttonBox.getSize().x-offset);
                    _text.move(-diff,0);
                    _selection.move(-diff,0);
                    _selectionText.move(-diff,0);
                }

            }
        }

        void TextButton::setCursorBlink() // Создает эффект мигания курсора
        {
            if(_status)
            {
                if(_selectionText.getString()!="")
                {
                    _cursor.setFillColor(sf::Color(255,255,255,0));
                }
                else
                {
                float elapsedTime=clock.getElapsedTime().asSeconds();
                if(elapsedTime>0.5)
                {
                    if(_cursor.getFillColor()==sf::Color(255,255,255,0))
                    {
                        _cursor.setFillColor(sf::Color(0,0,200,150));
                    }
                    else
                    {
                        _cursor.setFillColor(sf::Color(255,255,255,0));

                    }
                    clock.restart();
                }
                }
            }
            else
            {
                _cursor.setFillColor(sf::Color(255,255,255,0));
            }

        }

        void TextButton::selectionDrop() // Сброс выделения
        {
            if(_cursorPos<_selectionPos)
            setCursor(_cursorPos);
            else
            setCursor(_selectionPos);
            _selectionText.setString("");
            _selection.setSize(sf::Vector2f(0,0));
        }

        void TextButton::selectionDelete() // удаление выделеного
        {
            std::string string =_selectionText.getString();
            selectionDrop();
            str.erase(_cursorPos,string.size());
            _text.setString(str);
        }

        void TextButton::onPressKey(const sf::Event::KeyEvent& key) // обработчик нажатия функциональных клавиш и комбинаций клавиш
        {
            switch(key.code)
            {
            case sf::Keyboard::BackSpace:
                if(_cursorPos>0)
                {
                    if(_selectionText.getString()!="")
                    {
                        selectionDelete();
                    }
                    else
                    {
                    str.erase(_cursorPos-1,1);
                    _text.setString(str);
                    setCursor(_cursorPos-1);
                    }
                }
                break;
            case sf::Keyboard::Enter:
                selectionDrop();
                _status=Status::None;
                break;
            case sf::Keyboard::Delete:
                if(_cursorPos!=0 &&_cursorPos!=str.size())
                {
                    if(_selectionText.getString()!="")
                    {
                        selectionDelete();
                    }
                    else
                    {
                    str.erase(_cursorPos,1);
                    _text.setString(str);
                    }
                }
                break;
            case sf::Keyboard::Left:
                    if(key.shift)
                    {
                        if(_selectionPos>0)
                        {
                        --_selectionPos;
                        setSelection();
                        }
                    }
                    else
                    {
                        if(_selectionText.getString()!="")
                        {
                            if(_cursorPos>_selectionPos)
                            {
                                setCursor(_selectionPos+1);

                            }
                            else
                            {
                                setCursor(_cursorPos+1);
                            }
                            _selectionText.setString("");
                            _selection.setSize(sf::Vector2f(0,0));
                        }
                        if(_cursorPos>0)
                        setCursor(_cursorPos-1);
                    }
                break;
            case sf::Keyboard::Right:
                    if(key.shift)
                    {
                        if(_selectionPos < str.size())
                        {
                        ++_selectionPos;
                        setSelection();
                        }
                    }
                    else
                    {
                       if(_selectionText.getString()!="")
                        {
                            if(_cursorPos<_selectionPos)
                            {
                                setCursor(_selectionPos-1);

                            }
                            else
                            {
                                setCursor(_cursorPos-1);
                            }
                            _selectionText.setString("");
                            _selection.setSize(sf::Vector2f(0,0));
                        }
                        if(_cursorPos<str.size())
                        setCursor(_cursorPos+1);
                    }
                break;
            case sf::Keyboard::Home:
                selectionDrop();
                setCursor(0);
                break;
            case sf::Keyboard::End:
                selectionDrop();
                setCursor(str.size());
                break;
            case sf::Keyboard::Escape:
                selectionDrop();
                _status=Status::None;
                break;
            case sf::Keyboard::C:
                if(key.control)
                {
                    if(_selectionText.getString()!="")
                    {
                     const std::string string = _selectionText.getString();
                     sf::Clipboard::setString(string);

                    }
                }
                break;
            case sf::Keyboard::V:
                if(key.control)
                {
                   std::string string = sf::Clipboard::getString();
                   if(str.size()+string.size()<=strSize)
                    str.insert(_cursorPos,string);
                    _text.setString(str);
                    setCursor(_cursorPos+string.size());
                }
                break;
            case sf::Keyboard::X:
                if(key.control)
                {
                    const std::string string = _selectionText.getString();
                    sf::Clipboard::setString(string);
                    selectionDelete();
                }
                break;
            }
        }

        void TextButton::mouseCursorPos(float x, float y) // устанивливает курсор по нажатию кнопки мыши
        {
            select= false;
            x-=_position.x;
            y-=_position.y;
            for(int i = str.size(); i>=0;--i)
            {
                if(y>=_cursor.getPosition().y && y<=_cursor.getPosition().y+_cursor.getSize().y)
                {
                    if(x>=_text.findCharacterPos(i).x)
                    {
                        setCursor(i);
                        i=0;
                        select=true;
                    }
                }
            }
            if(_selectionText.getString()!="")
            {
                selectionDrop();
            }
        }

        void TextButton::mouseSelection(float x, float y) // Выделение при помощи мыши
        {
            x-=_position.x;
            if(x!=_cursor.getPosition().x)
            {
            for(int i = str.size(); i>=0;--i)
            {
                if(x>=_text.findCharacterPos(i).x)
                {
                    _selectionPos=i;
                    setSelection();
                    break;
                }
            }
            }

        }

        sf::Cursor& TextButton::setCursorSkin(float x, float y) // Установка стиля курсора
        {
            sf::FloatRect rect ;
            rect.left = _position.x;
            rect.top = _position.y;
            rect.width = _buttonBox.getSize().x+_buttonBox.getOutlineThickness();
            rect.height= _buttonBox.getSize().y+_buttonBox.getOutlineThickness();
            const sf::Vector2f mouse_pos(x,y);
            if(rect.contains(mouse_pos))
            {
               cursor.loadFromSystem(sf::Cursor::Text);
            }
            else
            {
                cursor.loadFromSystem(sf::Cursor::Arrow);
            }
            return cursor;
        }

        void TextButton::onMousePressed(float x, float y) // Обработчик нажатия кнопки мыши
        {
            sf::FloatRect rect ;
            rect.left = _position.x;
            rect.top = _position.y;
            rect.width = _buttonBox.getSize().x+_buttonBox.getOutlineThickness();
            rect.height= _buttonBox.getSize().y+_buttonBox.getOutlineThickness();
            const sf::Vector2f mouse_pos(x,y);
            if(rect.contains(mouse_pos))
            {
                _status = Status::Activ;
            }
        }

        void TextButton::processEvent(sf::Event& event) // Обработчик событий
        {
            switch(event.type)
            {
            case sf::Event::TextEntered:
                if(_status)
                {

                    if(_cursorPos==str.size())
                    {
                        setText(event.text.unicode);
                    }
                    else if(_cursorPos<str.size())
                    {
                        enterText(event.text.unicode);
                    }
                }
                break;
            case sf::Event::KeyPressed:
                if(_status)
                {onPressKey(event.key);}
                break;
            case sf::Event::MouseButtonReleased:
                if(!_status)
                onMousePressed(event.mouseButton.x,event.mouseButton.y);
                else
                select= false;
                break;
            case sf::Event::MouseButtonPressed:
                if(_status)
                mouseCursorPos(event.mouseButton.x,event.mouseButton.y);
                break;
            case sf::Event::MouseMoved:

                if(select)
                {
                    mouseSelection(event.mouseMove.x,event.mouseMove.y);
                }

                break;
            }
        }

        void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states)const // Отрисовка кнопки
        {
            states.transform.translate(_position);
            target.draw(_buttonBox,states);
            glEnable(GL_SCISSOR_TEST);
            glScissor(_position.x+offset,target.getSize().y-_position.y-_buttonBox.getSize().y,_buttonBox.getSize().x-offset*2,_buttonBox.getSize().y);
            target.draw(_text,states);

            target.draw(_selection,states);
            target.draw(_selectionText,states);
            glDisable(GL_SCISSOR_TEST);
            if(_status)
            target.draw(_cursor,states);
        }

}
