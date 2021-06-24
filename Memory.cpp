#include <SFML/Graphics.hpp>
#include <vector>

class Memory
{

public:
    sf::Text _text;
    sf::Text _selectionText;
    sf::RectangleShape _selection;
    Memory(sf::Text text,sf::Text selectionText, sf::RectangleShape selection): _text(text), _selectionText(selectionText), _selection(selection)
    {

    }

};

class MemoryList
{
private:
    static std::vector <Memory> reStack;
    static int num ;

public:
    void addMemory(Memory memory)
    {
        if(reStack.at(num)._text.getString()==memory._text.getString()
            && reStack.at(num)._selectionText.getString()==memory._selectionText.getString()
            && reStack.at(num)._selection.getSize().x==memory._selection.getSize().x)
        {
        }
        else
        {
        if(reStack.size()<=10)
        {
            ++num;
            reStack.push_back(memory);
        }
        else
        {
            reStack.erase(reStack.begin());
            reStack.resize(9);
            reStack.push_back(memory);
        }
        }
    }

    Memory undo()
    {
        --num;
        return reStack.at(num);
    }


};
