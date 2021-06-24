#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Shapes : public sf::Drawable
{
private:

    sf::ConvexShape _convShape;
    sf::Color _color;
    std::vector <sf::Vertex> _pointsC;
    std::vector <sf::Vertex> _pointsR;
    sf::RectangleShape _rectShape;

public:

    Shapes():_color(sf::Color(0,0,150,100))
    {
        _rectShape.setFillColor(_color);
        _convShape.setFillColor(_color);
    }

    void updateShape()
    {
        if(_pointsC.size())
        {
            _convShape.setPointCount(_pointsC.size());
            for(size_t i=0;i<_pointsC.size();++i)
            {
                _convShape.setPoint(i,_pointsC[i].position);
            }
        }
        std::cout<<"Для новой фигуры"<<"\n";
        for(size_t i =0; i<_pointsC.size();++i)
        {
            std::cout<<i<<" : x "<<_pointsC[i].position.x<<"\n";
            std::cout<<i<<" : y "<<_pointsC[i].position.y<<"\n";
        }

    }

    const sf::Vector2f& getPosition()const
    {
        return _rectShape.getPosition();
    }

    const sf::Vector2f& getSize()const
    {
        return _rectShape.getSize();
    }

    void setSize(sf::Vector2f _size)
    {
        _rectShape.setSize(_size);
    }

    void setRectPosition(float x , float y)
    {
        _rectShape.setPosition(x,y);
        setPointRect();
    }

    void setRectPosition(sf::Vector2f _position)
    {
        _rectShape.setPosition(_position);
        setPointRect();
    }

    void setConvPosition(float x , float y)
    {
        _convShape.setPosition(x,y);
        setPointConv();
    }

    void setConvPosition(sf::Vector2f _position)
    {
        _rectShape.setPosition(_position);
        setPointConv();
    }

    void divideShape()
    {

    }

    void unitShape()
    {
        if(_pointsC.size()==0)
        {
            for(size_t i=0;i<4;++i)
            {_pointsC.push_back(_pointsR[i]);}
        }
        else
        {
        _pointsC[0]=_pointsR[0];
        if(_pointsC[1].position.x==_pointsR[1].position.x)
        {
            _pointsC[1]=_pointsR[1];
        }
        else
        {
            _pointsC.emplace(_pointsC.begin()+1,_pointsR[1]);
            _pointsC.emplace(_pointsC.begin()+2,_pointsR[2]);
        }
        }
        updateShape();
    }

    void setPointRect()
    {
        _pointsR.clear();
        _pointsR.push_back(_rectShape.getPoint(0));
        _pointsR.push_back(_rectShape.getPoint(1));
        _pointsR.push_back(_rectShape.getPoint(2));
        _pointsR.push_back(_rectShape.getPoint(3));
        for(size_t i =0; i<4;++i)
        {
            std::cout<<i<<" : x "<<_pointsR[i].position.x<<"\n";
            std::cout<<i<<" : y "<<_pointsR[i].position.y<<"\n";
        }
    }

    void setPointConv()
    {
        for(size_t i=0;i<_pointsC.size();++i)
        {
            _pointsC[i]=_convShape.getPoint(i);
        }
    }

    bool checkSelection()
    {
        if(_pointsC.size()==0 && _rectShape.getSize().x==0)
        {
            return false;
        }
            return true;
    }

    virtual void draw(sf::RenderTarget& target,sf::RenderStates states)const override
    {
        target.draw(_rectShape,states);
        target.draw(_convShape,states);
    }

};
