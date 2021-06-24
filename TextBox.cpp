#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Widget.h"
#include <iostream>
#include <vector>




namespace gui
{
    class TextBox :public Widget
    {

    private:

        sf::Vector2f _position;
        std::vector <sf::Text> _text;
        std::vector <sf::RectangleShape> _selection;
        float _characterSize;
        sf::Font _font;
        sf::RectangleShape _cursor;
        sf::RectangleShape _buttonBox;
        sf::Vector2i _cursorPos;
        sf::Vector2i _selectionPos;
        float offset;
        int _status;
        bool mpres;
        sf::Clock clock;
        enum Status
        {
            None=0,
            Activ
        };

    public:

        TextBox(sf::Vector2f position = sf::Vector2f(0,0),
               unsigned int x=200,unsigned int y=200,float characterSize=14, Widget* parent=nullptr): _cursorPos(0,0), Widget(parent),_characterSize(characterSize)
        {
            _position=position;
            _font.loadFromFile("18028.ttf");
            _text.push_back(addString());
            _status=Status::None;
            _buttonBox.setFillColor(sf::Color::White);
            _buttonBox.setSize(sf::Vector2f(x,y));
            _buttonBox.setOutlineColor(sf::Color::Black);
            _buttonBox.setOutlineThickness(2);
            _position.x+=_buttonBox.getOutlineThickness();
            _position.y+=_buttonBox.getOutlineThickness();
            offset = 6;
            mpres=false;
            updateShape();
        }

        void updateShape() // Задание формы и расположения всех элементов кнопки
        {
            _text[0].setPosition(sf::Vector2f(offset,offset));
            _cursor.setSize(sf::Vector2f(2,_characterSize*1.3));
            _cursor.setPosition(sf::Vector2f(offset,offset));
        }

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override // Отрисовка кнопки
        {
            states.transform.translate(_position);
            target.draw(_buttonBox,states);
            glEnable(GL_SCISSOR_TEST);
            glScissor(_position.x+offset,target.getSize().y-_position.y-_buttonBox.getSize().y+offset,_buttonBox.getSize().x-offset*2,_buttonBox.getSize().y-offset*2);
            if(_selection.size()!=0)
            {
                for(auto select : _selection)
                target.draw(select,states);
            }
            for(auto text: _text)
            {
                target.draw(text,states);
            }
            glDisable(GL_SCISSOR_TEST);
            //if(_status)
            target.draw(_cursor,states);
            //target.draw(_selection,states);
        }

        void processEvent(sf::Event& event) // Обработчик событий
        {
            switch(event.type)
            {
            case sf::Event::TextEntered:
                //if(_status)
                //{
                    enterText(event.text.unicode);
                //}
                break;
            case sf::Event::KeyPressed:
                //if(_status)
                {onPressKey(event.key);}
                break;
            case sf::Event::MouseButtonReleased:
               // if(!_status)
            //    onMousePressed(event.mouseButton.x,event.mouseButton.y);
              //  else
          //      select= false;
                  mpres=false;
                break;
            case sf::Event::MouseButtonPressed:
                //if(_status)
                dropSelection();
                mouseCursorPos(event.mouseButton.x,event.mouseButton.y);
                mpres=true;
                break;
            case sf::Event::MouseMoved:
                if(mpres)
                {
                    mouseSelection(event.mouseMove.x,event.mouseMove.y);
                }

                break;
            }
        }

        void onPressKey(const sf::Event::KeyEvent& key) // обработчик нажатия функциональных клавиш и комбинаций клавиш
        {
            switch(key.code)
            {
            case sf::Keyboard::BackSpace:
               if(_selection.size()!=0)
               {
                 selectionDelete();
                 dropSelection();
               }
               else
                {
                    setBackSpace();
                }
                break;
            case sf::Keyboard::Enter:
                if(_selection.size()!=0)
               {
                 selectionDelete();
                 dropSelection();
               }
                setEnter();
                break;
            case sf::Keyboard::Delete:
               if(_selection.size()!=0)
               {
                 selectionDelete();
                 dropSelection();
               }
               else
               {
                   setDelete();
               }
                break;
            case sf::Keyboard::Left:
                if(key.shift)
                {
                    checkSel();
                    setLeft();
                    setSelectionLeft();
                }
                else
                {
                   setLeft();
                   dropSelection();
                }
                break;
            case sf::Keyboard::Right:
                if(key.shift)
                {
                    checkSel();
                    setRight();
                    setSelectionRight();
                }
                else
                {
                    setRight();
                    dropSelection();
                }
                break;
            case sf::Keyboard::Up:
                if(key.shift)
                {
                    checkSel();
                    setUp();
                    setSelectionLeft();
                }
                else
                {
                    setUp();
                    dropSelection();
                }
                break;
            case sf::Keyboard::Down:
                if(key.shift)
                {
                    checkSel();
                    setDown();
                    setSelectionRight();
                }
                else
                {
                    setDown();
                    dropSelection();
                }
                break;
            case sf::Keyboard::Home:
                _cursorPos.y=0;
                setCursor();
                break;
            case sf::Keyboard::End:
                {std::string str = _text[_cursorPos.x].getString();
                _cursorPos.y=str.size();
                setCursor();}
                break;
            case sf::Keyboard::C:
                if(key.control)
                {
                    if(_selection.size()!=0)
                    {
                        setTextCopy();
                    }
                }
                break;
            case sf::Keyboard::V:
                if(key.control)
                {
                    if(_selection.size()!=0)
                    {
                        selectionDelete();
                        dropSelection();
                    }
                    setTextInput();
                }
                break;
            case sf::Keyboard::X:
                if(key.control)
                {
                    if(_selection.size()!=0)
                    {
                        setTextCopy();
                        selectionDelete();
                        dropSelection();
                    }
                }
                break;
            }
        }

        sf::Text addString()
        {
            sf::Text text;
            text.setFillColor(sf::Color::Black);
            text.setCharacterSize(_characterSize);
            text.setFont(_font);
            text.setString("");
            return text;
        }

        void setCursorBlink() // Создает эффект мигания курсора
        {
            //if(_status)
            {
               // if(_selectionText.getString()!="")
                //{
                  //  _cursor.setFillColor(sf::Color(255,255,255,0));
                //}
                //else
                //{
                float elapsedTime=clock.getElapsedTime().asSeconds();
                if(elapsedTime>0.5)
                {
                    if(_cursor.getFillColor()==sf::Color(255,255,255,0))
                    {
                        _cursor.setFillColor(sf::Color(0,0,0,150));
                    }
                    else
                    {
                        _cursor.setFillColor(sf::Color(255,255,255,0));

                    }
                    clock.restart();
                }
                //}
            }
            //else
            //{
              //  _cursor.setFillColor(sf::Color(255,255,255,0));
            //}

        }

        void enterText(sf::Uint32 unicode) // Ввод текста с позиции курсора
        {
            if(_selection.size()!=0)
               {
                 selectionDelete();
                 dropSelection();
               }
            if(unicode>30 && (unicode<127||unicode>159))
            {
                    std::string str=_text[_cursorPos.x].getString();
                    str.insert(_cursorPos.y,1,unicode);
                    _text[_cursorPos.x].setString(str);
                    ++_cursorPos.y;
                    setCursor();
            }
        }

        void setCursor()
        {
            _cursor.setPosition(_text[_cursorPos.x].findCharacterPos(_cursorPos.y).x,_text[_cursorPos.x].findCharacterPos(_cursorPos.y).y);
            viewMove();
        }

        void setEnter()
        {
            std::string str = _text[_cursorPos.x].getString();
                if(_cursorPos.y==str.size())
                {
                ++_cursorPos.x;
                _text.emplace(_text.begin()+_cursorPos.x,addString());
                _cursorPos.y=0;
                }
                else
                {
                std::string string = str.substr(_cursorPos.y);
                str.erase(_cursorPos.y);
                _text[_cursorPos.x].setString(str);
                ++_cursorPos.x;
                _text.emplace(_text.begin()+_cursorPos.x,addString());
                _text[_cursorPos.x].setString(string);
                _cursorPos.y=0;
                }

                for(int i=0;i<_text.size();++i)
                {
                    _text[i].setPosition(sf::Vector2f(offset,offset+(_cursor.getSize().y*i)));
                }
                setCursor();
        }

        void setBackSpace()
        {
            if(_cursorPos.x+_cursorPos.y>0)
            {
                std::string str = _text[_cursorPos.x].getString();
                if(_cursorPos.y==0&&_cursorPos.x>0)
                {
                    _text.erase(_text.begin()+_cursorPos.x);
                    --_cursorPos.x;
                    std::string string =_text[_cursorPos.x].getString();
                    _cursorPos.y=string.size()+1;
                    string += str;
                    _text[_cursorPos.x].setString(string);
                    --_cursorPos.y;
                }
                else
                {
                str.erase(_cursorPos.y-1,1);
                _text[_cursorPos.x].setString(str);
                --_cursorPos.y;

                }
                for(int i=0;i<_text.size();++i)
                {
                    _text[i].setPosition(sf::Vector2f(offset,offset+(_cursor.getSize().y*i)));
                }
                setCursor();
            }
        }

        void setDelete()
        {
            if(_cursorPos.x+_cursorPos.y>0)
                {
                    std::string str = _text[_cursorPos.x].getString();
                    if(_cursorPos.y==0&&_cursorPos.x!=0&&str.size()==0)
                    {
                        _text.erase(_text.begin()+_cursorPos.x);
                        --_cursorPos.x;
                        std::string str = _text[_cursorPos.x].getString();
                        _cursorPos.y=str.size()+1;
                        --_cursorPos.y;
                    }
                    else
                    {
                    str.erase(_cursorPos.y,1);
                    _text[_cursorPos.x].setString(str);
                    }
                    for(int i=0;i<_text.size();++i)
                    {
                        _text[i].setPosition(sf::Vector2f(offset,offset+(_cursor.getSize().y*i)));
                    }
                    setCursor();
                }
        }

        void setLeft()
        {
            if(_cursorPos.y>0)
            {
                --_cursorPos.y;
            }
            else if(_cursorPos.x>0)
            {
                --_cursorPos.x;
                std::string str =_text[_cursorPos.x].getString();
                _cursorPos.y=str.size();
            }
            setCursor();
        }

        void setRight()
        {
            std::string str =_text[_cursorPos.x].getString();
            if(_cursorPos.y<str.size())
            {
                ++_cursorPos.y;
            }
            else if(_cursorPos.x<_text.size()-1)
            {
                ++_cursorPos.x;
                _cursorPos.y=0;
            }
            setCursor();
        }

        void setUp()
        {
            if(_cursorPos.x>0)
            {
                --_cursorPos.x;
                std::string str=_text[_cursorPos.x].getString();
                if(_cursorPos.y>str.size())
                {
                    _cursorPos.y=str.size();
                }
                setCursor();
            }

        }

        void setDown()
        {
            if(_cursorPos.x<_text.size()-1)
            {
                ++_cursorPos.x;
                std::string str=_text[_cursorPos.x].getString();
                if(_cursorPos.y>str.size())
                {
                    _cursorPos.y=str.size();
                }
                setCursor();
            }
        }

        void checkSel()
        {
            if(_selection.size()==0)
            {
                _selectionPos = _cursorPos;
                _selection.push_back(sf::RectangleShape());
                _selection[_selection.size()-1].setFillColor(sf::Color(81,140,255,170));
                _selection[_selection.size()-1].setPosition(_cursor.getPosition());
            }
        }

        void dropSelection()
        {
            _selection.clear();
        }

        void setSelectionLeft()
        {
            if(_selection[_selection.size()-1].getPosition().y !=_cursor.getPosition().y)
            {
                if(_cursor.getPosition().y==_selection[_selection.size()-2].getPosition().y)
                {
                    _selection.resize(_selection.size()-1);
                    std::string str=_text[_cursorPos.x].getString();
                     float size=_selection[_selection.size()-1].getSize().x+(_text[_cursorPos.x].findCharacterPos(str.size()).x-_cursor.getPosition().x);
                    _selection[_selection.size()-1].setPosition(_cursor.getPosition());
                    _selection[_selection.size()-1].setSize(sf::Vector2f(size,_cursor.getSize().y));
                }
                else
                {
                    sf::Vector2f _size=_selection[_selection.size()-1].getSize();
                    float size = _selection[_selection.size()-1].getPosition().x-_text[_cursorPos.x+1].findCharacterPos(0).x+_size.x;
                    _selection[_selection.size()-1].setPosition(_text[_cursorPos.x+1].findCharacterPos(0).x,_text[_cursorPos.x+1].findCharacterPos(0).y);
                    _selection[_selection.size()-1].setSize(sf::Vector2f(size,_cursor.getSize().y));
                    _selection.push_back(sf::RectangleShape());
                    _selection[_selection.size()-1].setFillColor(sf::Color(81,140,255,170));
                    _selection[_selection.size()-1].setPosition(_cursor.getPosition());
                    std::string str=_text[_cursorPos.x].getString();
                    size=_text[_cursorPos.x].findCharacterPos(str.size()).x-_cursor.getPosition().x;
                    _selection[_selection.size()-1].setSize(sf::Vector2f(size,_cursor.getSize().y));
                }
            }
            else
            {
            sf::Vector2f _pos=_selection[_selection.size()-1].getPosition();
            sf::Vector2f _size=_selection[_selection.size()-1].getSize();
            float size= _pos.x-_cursor.getPosition().x+_size.x;
            _selection[_selection.size()-1].setSize(sf::Vector2f(size,_cursor.getSize().y));
            _selection[_selection.size()-1].setPosition(_cursor.getPosition());
            }
        }

        void setSelectionRight()
        {
            if(_selection[_selection.size()-1].getPosition().y !=_cursor.getPosition().y)
            {
                if(_cursor.getPosition().y==_selection[_selection.size()-2].getPosition().y)
                {
                    _selection.resize(_selection.size()-1);
                    std::string str=_text[_cursorPos.x].getString();
                     float size=_selection[_selection.size()-1].getSize().x-(_cursor.getPosition().x-_text[_cursorPos.x].findCharacterPos(0).x);
                    _selection[_selection.size()-1].setPosition(_cursor.getPosition());
                    _selection[_selection.size()-1].setSize(sf::Vector2f(size,_cursor.getSize().y));
                }
                else
                {
                    std::string str=_text[_cursorPos.x-1].getString();
                    sf::Vector2f _size=_selection[_selection.size()-1].getSize();
                    float size = _selection[_selection.size()-1].getPosition().x-_text[_cursorPos.x-1].findCharacterPos(str.size()).x+_size.x;
                    _selection[_selection.size()-1].setPosition(_text[_cursorPos.x-1].findCharacterPos(str.size()).x,_text[_cursorPos.x-1].findCharacterPos(str.size()).y);
                    _selection[_selection.size()-1].setSize(sf::Vector2f(size,_cursor.getSize().y));
                    _selection.push_back(sf::RectangleShape());
                    _selection[_selection.size()-1].setFillColor(sf::Color(81,140,255,170));
                    _selection[_selection.size()-1].setPosition(_cursor.getPosition());
                    size=_text[_cursorPos.x].findCharacterPos(0).x-_cursor.getPosition().x;
                    _selection[_selection.size()-1].setSize(sf::Vector2f(size,_cursor.getSize().y));
                }
            }
            else
            {
            sf::Vector2f _pos=_selection[_selection.size()-1].getPosition();
            sf::Vector2f _size=_selection[_selection.size()-1].getSize();
            float size= _pos.x-_cursor.getPosition().x+_size.x;
            _selection[_selection.size()-1].setSize(sf::Vector2f(size,_cursor.getSize().y));
            _selection[_selection.size()-1].setPosition(_cursor.getPosition());
            }
        }

        void viewMove()
        {
            if(_cursor.getPosition().x>_buttonBox.getSize().x-offset)
            {
                float diff = _cursor.getPosition().x-(_buttonBox.getSize().x-offset);
                _cursor.move(-diff,0);
                for(size_t i = 0;i<_text.size();++i)
                {
                    _text[i].move(-diff,0);
                }
                if(_selection.size()!=0)
                {
                    for(size_t i = 0;i<_selection.size();++i)
                    {
                        _selection[i].move(-diff,0);
                    }
                }
            }
            if(_cursor.getPosition().x<offset)
            {
                float diff = offset - _cursor.getPosition().x;
                 _cursor.move(diff,0);
                for(size_t i = 0;i<_text.size();++i)
                {
                    _text[i].move(diff,0);
                }
                if(_selection.size()!=0)
                {
                    for(size_t i = 0;i<_selection.size();++i)
                    {
                        _selection[i].move(diff,0);
                    }
                }
            }


            if(_cursor.getPosition().y+_cursor.getSize().y>_buttonBox.getSize().y-offset)
            {
                float diff = _cursor.getPosition().y+_cursor.getSize().y-(_buttonBox.getSize().y-offset);
                _cursor.move(0,-diff);
                for(size_t i = 0;i<_text.size();++i)
                {
                    _text[i].move(0,-diff);
                }
                if(_selection.size()!=0)
                {
                    for(size_t i = 0;i<_selection.size();++i)
                    {
                        _selection[i].move(0,-diff);
                    }
                }
            }
            if(_cursor.getPosition().y<offset)
            {
                float diff = offset - _cursor.getPosition().y;
                 _cursor.move(0,diff);
                for(size_t i = 0;i<_text.size();++i)
                {
                    _text[i].move(0,diff);
                }
                if(_selection.size()!=0)
                {
                    for(size_t i = 0;i<_selection.size();++i)
                    {
                        _selection[i].move(0,diff);
                    }
                }
            }
        }

        void selectionDelete()
        {
                if(_cursorPos.x<_selectionPos.x)
                {
                    sf::Vector2i swp=_cursorPos;
                    _cursorPos=_selectionPos;
                    _selectionPos=swp;
                }
                if(_cursorPos.x==_selectionPos.x)
                {
                    std::string str=_text[_selectionPos.x].getString();
                    if(_cursorPos.y>_selectionPos.y)
                    {
                        int po= _cursorPos.y;
                        _cursorPos.y=_selectionPos.y;
                        _selectionPos.y=po;
                    }
                    int del_s =_selectionPos.y-_cursorPos.y;
                    str.erase(_cursorPos.y,del_s);
                    _text[_selectionPos.x].setString(str);
                }
                else
                {
                    std::string str=_text[_selectionPos.x].getString();
                    str.erase(_selectionPos.y);
                    std::string string=str;
                    str=_text[_cursorPos.x].getString();
                    str.erase(0,_cursorPos.y);
                    string+=str;
                    _text.erase(_text.begin()+_selectionPos.x,_text.begin()+_cursorPos.x);
                    _text[_selectionPos.x].setString(string);
                    _cursorPos=_selectionPos;
                }
                for(int i=0;i<_text.size();++i)
                {
                    _text[i].setPosition(sf::Vector2f(offset,offset+(_cursor.getSize().y*i)));
                }
                setCursor();
        }

        void setTextCopy()
        {
                std::string str;
                std::string string="";
                if(_cursorPos.x==_selectionPos.x)
                {
                    str=_text[_selectionPos.x].getString();
                    if(_selectionPos.y>_cursorPos.y)
                    {
                        int cut =_selectionPos.y-_cursorPos.y;
                        string = str.substr(_cursorPos.y,cut);
                    }
                    else
                    {
                        int cut =_cursorPos.y-_selectionPos.y;
                        string = str.substr(_selectionPos.y,cut);
                    }
                }
                else
                {
                    sf::Vector2i pos1;
                    sf::Vector2i pos2;
                    if(_cursorPos.x>_selectionPos.x)
                    {
                        pos1=_selectionPos;
                        pos2=_cursorPos;
                    }
                    else
                    {
                        pos1=_cursorPos;
                        pos2=_selectionPos;
                    }
                    for(int i = pos1.x;i<=pos2.x;++i)
                    {
                        if(i==pos1.x)
                        {
                            str=_text[i].getString();
                            string+= str.substr(pos1.y);
                        }
                        else if(i==pos2.x)
                        {
                            string+="\r\n";
                            str=_text[i].getString();
                            string+= str.substr(0,pos2.y);
                        }
                        else
                        {
                            string+="\r\n";
                            str=_text[i].getString();
                            string += str;
                        }
                    }
                }
                sf::Clipboard::setString(string);
        }

        void setTextInput()
        {
            std::string string = sf::Clipboard::getString();
            std::string str="";
            if(string.size()!=0)
            {
                for(char ch: string)
                {
                    if(ch=='\n')
                    {
                        std::string cv=_text[_cursorPos.x].getString();
                        cv.insert(_cursorPos.y,str);
                        _text[_cursorPos.x].setString(cv);
                        _cursorPos.y+=str.size();
                        str="";
                        setEnter();
                    }
                    else if (ch!='\r')
                    {
                        str +=ch;

                    }
                }
                if(str!="")
                {
                    std::string cv=_text[_cursorPos.x].getString();
                    cv.insert(_cursorPos.y,str);
                    _text[_cursorPos.x].setString(cv);
                    _cursorPos.y+=str.size();
                }
                setCursor();
            }
        }
        void mouseCursorPos(float x, float y)
        {
            x-=_position.x;
            y-=_position.y;
            for(int i =_text.size()-1;i>=0;--i)
            {
                if(y>=_text[i].getPosition().y&&y<=_text[i].getPosition().y+_cursor.getSize().y)
                {
                    std::string str =_text[i].getString();
                    for(int j = str.size();j>=0;--j)
                    {
                        if(x>=_text[i].findCharacterPos(j).x)
                        {
                            _cursorPos=sf::Vector2i(i,j);
                            i=0;
                            j=0;
                        }
                    }
                }
            }
            setCursor();
        }
        void mouseSelection(float x, float y)
        {
            mouseCursorPos(x,y);
            checkSel();
            if(_cursorPos.x>_selectionPos.x)
            {
                setSelectionRight();
            }
            else if(_cursorPos.x==_selectionPos.x)
            {
                if(_cursorPos.y>_selectionPos.y)
                {
                    setSelectionRight();
                }
                else if(_cursorPos.y<_selectionPos.y)
                {
                    setSelectionLeft();
                }
            }
            else if(_cursorPos.x<_selectionPos.x)
            {
                setSelectionLeft();
            }
        }
    };
}
