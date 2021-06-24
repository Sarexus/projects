#include <SFML/Graphics.hpp>
#include "GUI.h"


using namespace gui;

int main()
{
    std::setlocale(0,"");
    sf::RenderWindow window(sf::VideoMode(800,600),"GUI_0.1");
    Label *label=new Label("Борись",100,sf::Vector2f(100,100));
    TextButton *button= new TextButton();
    TextBox *box = new TextBox(sf::Vector2f(200,250));
    Conteiner conteiner;
    conteiner.addWidget(label);
    conteiner.addWidget(button);
    conteiner.addWidget(box);

    while(window.isOpen())
    {
        sf::Event event;
        if(window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
            {
                window.close();
            }
            conteiner.processEvent(event);
        }

        window.clear(sf::Color::White);
        window.draw(conteiner);
        button->setCursorBlink();
        box->setCursorBlink();
        window.setMouseCursor(button->setCursorSkin(event.mouseMove.x,event.mouseMove.y));
        window.display();
    }
    return 0;
}
