#ifndef CHESS_QUEEN_HPP
#define CHESS_QUEEN_HPP

#include "piece.hpp"

class Queen : public Piece
{
    public:
        Queen(Texture *tx, Vector2i vec, enum color color) : Piece(tx, vec, color, queen) {}
};

#endif