#ifndef CHESS_PIECE_HPP
#define CHESS_PIECE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

enum piece_value{non=0, king=-1, pawn=1, knight=2, bishop=3, rook=5, queen=9};
enum color{white=1, black=0, noColor=-1};

class Piece : public Drawable
{
    private:
        Texture *texture;
        Sprite sprite;
        color color;
        piece_value kind;
        virtual void draw(RenderTarget& target, RenderStates states) const
        {
            target.draw(sprite, states);
        }
    public:
        bool didMove;
        bool canBeEnPassaned;
        Piece();
        Piece(Texture*, Vector2i, enum color);
        Piece(Texture*, Vector2i, enum color, enum piece_value);
        void setPosition(int, int);
        void setPosition(Vector2i);
        Vector2f getPosition();
        void move(int, int);
        void move(Vector2i);
        void setTexture(Texture*);
        Texture* getTexture();
        enum piece_value getPiece();
        enum color getColor();
        bool isNull();
        void fix();
        void discombobulate();
};

#endif
