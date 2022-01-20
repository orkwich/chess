#ifndef CHESS_BOARD_HPP
#define CHESS_BOARD_HPP

#define RES 800
#define FPS 120

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "pawn.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "kinght.hpp"
#include "queen.hpp"
#include "king.hpp"
using namespace sf;
using namespace std;

class Board : public Drawable
{
    private:
        Vector2f resolution=Vector2f(RES,RES);
        RenderWindow window;
        Sprite background;
        Texture *queenTextureWhite;
        Texture *queenTextureBlack;

        Piece board[8][8];
        bool attacksWhite[8][8];
        bool attacksBlack[8][8];
        bool mat;
        int moveCount;
        int whiteScore;
        int blackScore;

        virtual void draw(RenderTarget& target, RenderStates states) const
        {
            target.draw(background, states);
            for(int i=0;i<8;i++)
                for(int j=0;j<8;j++) target.draw(board[i][j], states);
        }
    public:
        Board(Texture *, Texture *, Texture *, Texture *, Texture *, Texture *, Texture *, Texture *, Texture *, Texture *, Texture *, Texture *, Texture *);
        bool tryMove(Vector2i, Vector2i, bool);
        bool tryPawnMove(Vector2i, Vector2i, bool);
        bool tryKnightMove(Vector2i, Vector2i, bool);
        bool tryBishopMove(Vector2i, Vector2i, bool);
        bool tryRookMove(Vector2i, Vector2i, bool);
        bool tryQueenMove(Vector2i, Vector2i, bool);
        bool tryKingMove(Vector2i, Vector2i, bool[8][8], bool);
        void tryPawnPromotion(enum color color);
        bool capture(Vector2i, Vector2i, bool, bool);
        bool tryCapture(Vector2i, Vector2i, bool);
        void enPassantUpdate(enum color color);
        void updateStuffAfterMove();
        void attacksUpdate();
        vector<Vector2i> pawnMoves(Vector2i);
        vector<Vector2i> knightMoves(Vector2i);
        vector<Vector2i> bishopMoves(Vector2i);
        vector<Vector2i> rookMoves(Vector2i);
        vector<Vector2i> queenMoves(Vector2i);
        vector<Vector2i> kingMoves(Vector2i);
        void pawnAttacksUpdate(bool[8][8], Vector2i);
        void bishopAttacksUpdate(bool[8][8], Vector2i);
        void knightAttacksUpdate(bool[8][8], Vector2i);
        void rookAttacksUpdate(bool[8][8], Vector2i);
        void queenAttacksUpdate(bool[8][8], Vector2i);
        void kingAttacksUpdate(bool[8][8], Vector2i);
        void scoreUpdate(Vector2i, Vector2i);
        void fix();
        void draw();
        void input();
        void run();
        void enPassantCheck();
        void showAttacks();
        bool isCoordGood(Vector2i);
        bool isCheck(enum color);
        bool isMat(enum color);
};

#endif