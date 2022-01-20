#include "piece.hpp"

Piece::Piece()
{
    this->texture=nullptr;
    this->kind=non;
    this->color=noColor;
    this->didMove=0;
    this->canBeEnPassaned=0;
}

Piece::Piece(Texture *tx, Vector2i vec, enum color color)
{
    this->texture=tx;
    this->color=color;
    this->kind=non;
    this->didMove=0;
    this->canBeEnPassaned=0;
    this->sprite.setTextureRect(IntRect(Vector2i(0,0),Vector2i(100,100)));
    this->sprite.setTexture(*this->texture);
    this->sprite.setOrigin(50,50);
    this->sprite.setPosition(vec.x*100+50,vec.y*100+50);
}

Piece::Piece(Texture *tx, Vector2i vec, enum color color, enum piece_value val)
{
    this->texture=tx;
    this->color=color;
    this->kind=val;
    this->didMove=0;
    this->canBeEnPassaned=0;
    this->sprite.setTextureRect(IntRect(Vector2i(0,0),Vector2i(100,100)));
    this->sprite.setTexture(*this->texture);
    this->sprite.setOrigin(50,50);
    this->sprite.setPosition(vec.x*100+50,vec.y*100+50);
}

void Piece::setPosition(int x, int y)
{
    this->sprite.setPosition(x,y);
}

void Piece::setPosition(Vector2i vec)
{
    this->sprite.setPosition(vec.x,vec.y);
}

Vector2f Piece::getPosition()
{
    return this->sprite.getPosition();
}

void Piece::move(int x, int y)
{
    this->sprite.move(x,y);
}

void Piece::move(Vector2i vec)
{
    this->sprite.move(vec.x,vec.y);
}

void Piece::setTexture(Texture *tx)
{
    this->texture=tx;
}

Texture* Piece::getTexture()
{
    return this->texture;
}

enum piece_value Piece::getPiece()
{
    return this->kind;
}

enum color Piece::getColor()
{
    return this->color;
}

bool Piece::isNull()
{
    if(texture==nullptr && kind==non && color==noColor) return 1;
    return 0;
}

void Piece::fix()
{
    Vector2f tmp=sprite.getPosition();
    sprite.setPosition(tmp.x-(int(tmp.x)%100)+50,tmp.y-(int(tmp.y)%100)+50);
}

void Piece::discombobulate()
{
    texture=nullptr;
    sprite.setTexture(*texture);
    kind=non;
    color=noColor;
    this->didMove=0;
    this->canBeEnPassaned=0;
}