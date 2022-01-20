#ifndef CHESS_KING_HPP
#define CHESS_KING_HPP

#include "piece.hpp"

class King : public Piece
{
    public:
        King(Texture *tx, Vector2i vec, enum color color) : Piece(tx, vec, color, king) {}
};

#endif