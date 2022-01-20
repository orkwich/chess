#include <iostream>
#include "board.hpp"
using namespace std;

int main()
{
    Texture bg;
    bg.loadFromFile("img/szachownica.png");
    bg.setRepeated(1);

    Texture king, queen, rook, bish, knight, pawn, kingB, queenB, rookB, bishB, knightB, pawnB;

    king.loadFromFile("img/figury/king_white.png");
    queen.loadFromFile("img/figury/queen_white.png");
    rook.loadFromFile("img/figury/rook_white.png");
    bish.loadFromFile("img/figury/bishop_white.png");
    knight.loadFromFile("img/figury/knight_white.png");
    pawn.loadFromFile("img/figury/pawn_white.png");
    
    //kingB.loadFromFile("img/figury/king_white.png");
    //queenB.loadFromFile("img/figury/queen_white.png");
    //rookB.loadFromFile("img/figury/rook_white.png");
    //bishB.loadFromFile("img/figury/bishop_white.png");
    //knightB.loadFromFile("img/figury/knight_white.png");
    //pawnB.loadFromFile("img/figury/pawn_white.png");

    kingB.loadFromFile("img/figury/king_black.png");
    queenB.loadFromFile("img/figury/queen_black.png");
    rookB.loadFromFile("img/figury/rook_black.png");
    bishB.loadFromFile("img/figury/bishop_black.png");
    knightB.loadFromFile("img/figury/knight_black.png");
    pawnB.loadFromFile("img/figury/pawn_black.png");

    Board board(&bg,&pawn,&pawnB,&rook,&rookB,&knight,&knightB,&bish,&bishB,&queen,&queenB,&king,&kingB);
    board.run();
    return 0;
}
