#ifndef CHESS_BISHOP_HPP
#define CHESS_BISHOP_HPP

#include "piece.hpp"

class Bishop : public Piece
{
    public:
        Bishop(Texture *tx, Vector2i vec, enum color color) : Piece(tx, vec, color, bishop) {}
};

#endif