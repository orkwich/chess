#ifndef CHESS_ROOK_HPP
#define CHESS_ROOK_HPP

#include "piece.hpp"

class Rook : public Piece
{
    public:
        Rook(Texture *tx, Vector2i vec, enum color color) : Piece(tx, vec, color, rook) {}
};

#endif