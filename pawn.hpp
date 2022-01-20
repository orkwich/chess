#ifndef CHESS_PAWN_HPP
#define CHESS_PAWN_HPP

#include "piece.hpp"

class Pawn : public Piece
{
    public:
        Pawn(Texture *tx, Vector2i vec, enum color color) : Piece(tx, vec, color, pawn) {}
};

#endif