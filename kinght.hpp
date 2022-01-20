#ifndef CHESS_KNIGHT_HPP
#define CHESS_KNIGHT_HPP

#include "piece.hpp"

class Knight : public Piece
{
    public:
        Knight(Texture *tx, Vector2i vec, enum color color) : Piece(tx, vec, color, knight) {}
};

#endif