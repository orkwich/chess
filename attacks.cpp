#include "board.hpp"

void Board::pawnAttacksUpdate(bool board[8][8], Vector2i coord)
{
    vector<Vector2i> v = pawnMoves(coord);
    for(int i=0;i<v.size();i++) board[v[i].x][v[i].y] = 1;
}

void Board::knightAttacksUpdate(bool board[8][8], Vector2i coord)
{
    vector<Vector2i> v = knightMoves(coord);
    for(int i=0;i<v.size();i++) board[v[i].x][v[i].y] = 1;
}

void Board::bishopAttacksUpdate(bool board[8][8], Vector2i coord)
{
    vector<Vector2i> v = bishopMoves(coord);
    for(int i=0;i<v.size();i++) board[v[i].x][v[i].y] = 1;
}

void Board::rookAttacksUpdate(bool board[8][8], Vector2i coord)
{
    vector<Vector2i> v = rookMoves(coord);
    for(int i=0;i<v.size();i++) board[v[i].x][v[i].y] = 1;
}

void Board::queenAttacksUpdate(bool board[8][8], Vector2i coord)
{
    rookAttacksUpdate(board,coord);
    bishopAttacksUpdate(board,coord);
}

void Board::kingAttacksUpdate(bool board[8][8], Vector2i coord)
{
    vector<Vector2i> v = kingMoves(coord);
    for(int i=0;i<v.size();i++) board[v[i].x][v[i].y] = 1;
}

void Board::showAttacks()
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(attacksBlack[j][i]) cout<<"B ";
            else cout<<"0 ";
        }
        cout<<'\n';
    }
    cout<<'\n';
    cout<<'\n';
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(attacksWhite[j][i]) cout<<"W ";
            else cout<<"0 ";
        }
        cout<<'\n';
    }
    cout<<'\n';
    cout<<'\n';
}

void Board::attacksUpdate()
{
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            attacksWhite[i][j]=0;
            attacksBlack[i][j]=0;
        }
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            enum piece_value piece = board[i][j].getPiece();
            enum color color = board[i][j].getColor();
            switch(piece)
            {
                case non:
                {
                    break;
                }
                case pawn:
                {
                    if(color==white)
                    {
                        pawnAttacksUpdate(attacksWhite,Vector2i(i,j));
                        break;
                    }
                    pawnAttacksUpdate(attacksBlack,Vector2i(i,j));
                    break;
                }
                case knight:
                {
                    if(color==white)
                    {
                        knightAttacksUpdate(attacksWhite,Vector2i(i,j));
                        break;
                    }
                    knightAttacksUpdate(attacksBlack,Vector2i(i,j));
                    break;
                }
                case bishop:
                {
                    if(color==white)
                    {
                        bishopAttacksUpdate(attacksWhite,Vector2i(i,j));
                        break;
                    }
                    bishopAttacksUpdate(attacksBlack,Vector2i(i,j));
                    break;
                }
                case rook:
                {
                    if(color==white)
                    {
                        rookAttacksUpdate(attacksWhite,Vector2i(i,j));
                        break;
                    }
                    rookAttacksUpdate(attacksBlack,Vector2i(i,j));
                    break;
                }
                case queen:
                {
                    if(color==white)
                    {
                        queenAttacksUpdate(attacksWhite,Vector2i(i,j));
                        break;
                    }
                    queenAttacksUpdate(attacksBlack,Vector2i(i,j));
                    break;
                }
                case king:
                {
                    if(color==white)
                    {
                        kingAttacksUpdate(attacksWhite,Vector2i(i,j));
                        break;
                    }
                    kingAttacksUpdate(attacksBlack,Vector2i(i,j));
                    break;
                }
            }
        }
    }
}