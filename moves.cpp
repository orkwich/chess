#include "board.hpp"

vector<Vector2i> Board::pawnMoves(Vector2i coord)
{
    vector<Vector2i> v;
    int direction=1;
    if(board[coord.x][coord.y].getColor()==white)
    {
        if(coord.y==0) return v;
        direction=-1;
    }
    if(direction==1 && coord.y==7) return v; 
    if(coord.x!=0) v.push_back(Vector2i(coord.x-1,coord.y+direction));
    if(coord.x!=7) v.push_back(Vector2i(coord.x+1,coord.y+direction));
    return v;
}

vector<Vector2i> Board::knightMoves(Vector2i coord)
{
    vector<Vector2i> v;
    if(coord.x-2>=0 && coord.y-1>=0) v.push_back(Vector2i(coord.x-2,coord.y-1));
    if(coord.x-1>=0 && coord.y-2>=0) v.push_back(Vector2i(coord.x-1,coord.y-2));
    if(coord.x-2>=0 && coord.y+1<=7) v.push_back(Vector2i(coord.x-2,coord.y+1));
    if(coord.x-1>=0 && coord.y+2<=7) v.push_back(Vector2i(coord.x-1,coord.y+2));
    if(coord.x+2<=7 && coord.y+1<=7) v.push_back(Vector2i(coord.x+2,coord.y+1));
    if(coord.x+1<=7 && coord.y+2<=7) v.push_back(Vector2i(coord.x+1,coord.y+2));
    if(coord.x+2<=7 && coord.y-1>=0) v.push_back(Vector2i(coord.x+2,coord.y-1));
    if(coord.x+1<=7 && coord.y-2>=0) v.push_back(Vector2i(coord.x+1,coord.y-2));
    return v;
}

vector<Vector2i> Board::bishopMoves(Vector2i coord)
{
    vector<Vector2i> v;
    bool lg=1,pg=1,pd=1,ld=1;
    for(int q=1;q<=7;q++)
    {
        if(coord.x-q>=0)
        {
            if(coord.y-q>=0 && lg)
            {
                v.push_back(Vector2i(coord.x-q,coord.y-q));
                if(!this->board[coord.x-q][coord.y-q].isNull()) lg=0;
            }
            if(coord.y+q<=7 && ld)
            {
                v.push_back(Vector2i(coord.x-q,coord.y+q));
                if(!this->board[coord.x-q][coord.y+q].isNull()) ld=0;
            }
        }
        if(coord.x+q<=7)
        {
            if(coord.y-q>=0 && pg)
            {
                v.push_back(Vector2i(coord.x+q,coord.y-q));
                if(!this->board[coord.x+q][coord.y-q].isNull()) pg=0;
            }
            if(coord.y+q<=7 && pd)
            {
                v.push_back(Vector2i(coord.x+q,coord.y+q));
                if(!this->board[coord.x+q][coord.y+q].isNull()) pd=0;
            }
        }
    }
    return v;
}

vector<Vector2i> Board::rookMoves(Vector2i coord)
{
    vector<Vector2i> v;
    bool p=1,l=1,g=1,d=1;
    for(int i=1;i<=7;i++)
    {
        if(coord.x-i>=0 && l)
        {
            v.push_back(Vector2i(coord.x-i,coord.y));
            if(!this->board[coord.x-i][coord.y].isNull()) l=0;
        }
        if(coord.x+i<=7 && p)
        {
            v.push_back(Vector2i(coord.x+i,coord.y));
            if(!this->board[coord.x+i][coord.y].isNull()) p=0;
        }
        if(coord.y-i>=0 && g)
        {
            v.push_back(Vector2i(coord.x,coord.y-i));
            if(!this->board[coord.x][coord.y-i].isNull()) g=0;
        }
        if(coord.y+i<=7 && d)
        {
            v.push_back(Vector2i(coord.x,coord.y+i));
            if(!this->board[coord.x][coord.y+i].isNull()) d=0;
        }
    }
    return v;
}

vector<Vector2i> Board::queenMoves(Vector2i coord)
{
    vector<Vector2i> v = rookMoves(coord);
    vector<Vector2i> tmp = bishopMoves(coord);
    for(int i=0;i<tmp.size();i++) v.push_back(tmp[i]);
    return v;
}

vector<Vector2i> Board::kingMoves(Vector2i coord)
{
    vector<Vector2i> v;
    for(int i=-1;i<2;i++)
    {
        if(i==-1 && coord.x==0) continue;
        if(i==1 && coord.x==7) continue;
        for(int j=-1;j<2;j++)
        {
            if(i==j) continue;
            if(j==-1 && coord.y==0) continue;
            if(j==1 && coord.y==7) continue;
            v.push_back(Vector2i(coord.x+i,coord.y+j));
        }
    }
    return v;
}

bool Board::tryPawnMove(Vector2i from, Vector2i to, bool doCommit)
{
    enum color color = board[from.x][from.y].getColor();
    if(color==board[to.x][to.y].getColor()) return 0;
    if(color==black)
    {
        if(from.y>=to.y) return 0;
        if(from.x==to.x)
        {
            if(to.y-from.y==1 && board[to.x][to.y].isNull())
            {
                if(capture(from,to,0,doCommit))
                {
                    if(doCommit) updateStuffAfterMove();
                    return 1;
                }
                return 0;
            }
            if(to.y-from.y==2 && board[to.x][to.y-1].isNull() && board[to.x][to.y].isNull() && from.y==1)
            {
                if(capture(from,to,0,doCommit))
                {
                    if(doCommit)
                    {
                        board[to.x][to.y].canBeEnPassaned=1;
                        updateStuffAfterMove();
                    }
                    return 1;
                }
                return 0;
            }
        } else if(abs(from.x-to.x)==1)
        {
            if(board[to.x][to.y].isNull()) //en passant
            {
                if(board[to.x][from.y].canBeEnPassaned)
                {
                    if(capture(from,to,1,doCommit))
                    {
                        if(doCommit)
                        {
                            blackScore++;
                            updateStuffAfterMove();
                        }
                        return 1;
                    }
                    return 0;
                }
            } else //normal capture
            {
                int tmp = board[to.x][to.y].getPiece();
                if(capture(from,to,0,doCommit))
                {
                    if(doCommit)
                    {
                        blackScore+=tmp;
                        updateStuffAfterMove();
                    }
                    return 1;
                }
                return 0;
            }
        }
    } else if(color==white)
    {
        if(from.y<=to.y) return 0;
        if(from.x==to.x)
        {
            if(from.y-to.y==1 && board[to.x][to.y].isNull())
            {
                if(capture(from,to,0,doCommit))
                {
                    if(doCommit) updateStuffAfterMove();
                    return 1;
                }
                return 0;
            }
            if(from.y-to.y==2 && board[to.x][to.y+1].isNull() && board[to.x][to.y].isNull() && from.y==6)
            {
                if(capture(from,to,0,doCommit))
                {
                    if(doCommit)
                    {
                        board[to.x][to.y].canBeEnPassaned=1;
                        updateStuffAfterMove();
                    }
                    return 1;
                }
                return 0;
            }
        } else if(abs(from.x-to.x)==1)
        {
            if(board[to.x][to.y].isNull()) //en passant
            {
                if(board[to.x][from.y].canBeEnPassaned)
                {
                    if(capture(from,to,1,doCommit))
                    {
                        if(doCommit)
                        {
                            whiteScore++;
                            updateStuffAfterMove();
                        }
                        return 1;
                    }
                    return 0;
                }
            } else //normal capture
            {
                int tmp = board[to.x][to.y].getPiece();
                if(capture(from,to,0,doCommit))
                {
                    if(doCommit)
                    {
                        whiteScore+=tmp;
                        updateStuffAfterMove();
                    }
                    return 1;
                }
                return 0;
            }
        }
    } else cout<<"pawn without color???\n"; //should never happend
    return 0;
}

bool Board::tryKnightMove(Vector2i from, Vector2i to, bool doCommit)
{
    if(!((abs(from.x-to.x)==2 && abs(from.y-to.y)==1) || (abs(from.x-to.x)==1 && abs(from.y-to.y)==2))) return 0;
    return tryCapture(from,to,doCommit);
}

bool Board::tryBishopMove(Vector2i from, Vector2i to, bool doCommit)
{
    if(abs(from.x-to.x)==abs(from.y-to.y))
    {
        int xDirection=1, yDirection=1;
        if(from.x-to.x<0) xDirection=-1;
        if(from.y-to.y<0) yDirection=-1;
        for(int i=1;i<abs(from.x-to.x);i++)
            if(!board[from.x-(i*xDirection)][from.y-(i*yDirection)].isNull()) return 0;
        return tryCapture(from,to,doCommit);
    }
    return 0;
}

bool Board::tryRookMove(Vector2i from, Vector2i to, bool doCommit)
{
    if(from.x==to.x)
    {
        int up=1;
        if(from.y>to.y) up=-1;
        for(int i=1;i<abs(from.y-to.y);i++)
            if(!board[from.x][from.y+(i*up)].isNull()) return 0;
    } else if(from.y==to.y)
    {
        int left=1;
        if(from.x>to.x) left=-1;
        for(int i=1;i<abs(from.x-to.x);i++)
            if(!board[from.x+(i*left)][from.y].isNull()) return 0;
    } else return 0;
    return tryCapture(from,to,doCommit);
}

bool Board::tryQueenMove(Vector2i from, Vector2i to, bool doCommit)
{
    if(from.x==to.x)
    {
        int up=1;
        if(from.y>to.y) up=-1;
        for(int i=1;i<abs(from.y-to.y);i++)
            if(!board[from.x][from.y+(i*up)].isNull()) return 0;
    } else if(from.y==to.y)
    {
        int left=1;
        if(from.x>to.x) left=-1;
        for(int i=1;i<abs(from.x-to.x);i++)
            if(!board[from.x+(i*left)][from.y].isNull()) return 0;
    } else if(abs(from.x-to.x)==abs(from.y-to.y))
    {
        int xDirection=1, yDirection=1;
        if(from.x-to.x<0) xDirection=-1;
        if(from.y-to.y<0) yDirection=-1;
        for(int i=1;i<abs(from.x-to.x);i++)
            if(!board[from.x-(i*xDirection)][from.y-(i*yDirection)].isNull()) return 0;
    } else return 0;
    return tryCapture(from,to,doCommit);
}

bool Board::tryKingMove(Vector2i from, Vector2i to, bool attacks[8][8], bool doCommit)
{
    if((abs(from.x-to.x)==1 || abs(from.x-to.x)==0) && (abs(from.y-to.y)==1 || abs(from.y-to.y)==0))
    {
        return tryCapture(from,to,doCommit);
    } else if(!board[from.x][from.y].didMove)
    {
        int line=0;
        if(board[from.x][from.y].getColor()==white) line=7;
        if(line && isCheck(white)) return 0;
        if(line==0 && isCheck(black)) return 0;
        if(to.x-from.x==2 && board[7][line].getPiece()==rook && !board[7][line].didMove && board[6][line].isNull() && board[5][line].isNull() && attacks[6][line]==0 && attacks[5][line]==0) //short castle
        {
            capture(from,to,0,doCommit);
            capture(Vector2i(7,line),Vector2i(5,line),0,doCommit);
            if(doCommit) updateStuffAfterMove();
            return 1;
        } else if(from.x-to.x==2 && board[0][line].getPiece()==rook && !board[0][line].didMove && board[3][line].isNull() && board[2][line].isNull() && board[1][line].isNull() && attacks[3][line]==0 && attacks[2][line]==0) //long castle
        {
            capture(from,to,0,doCommit);
            capture(Vector2i(0,line),Vector2i(3,line),0,doCommit);
            if(doCommit) updateStuffAfterMove();
            return 1;
        }
    }
    return 0;
}

bool Board::isCheck(enum color color)
{
    attacksUpdate();
    if(color==white)
    {
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                if(board[i][j].getPiece()==king && board[i][j].getColor()==white && attacksBlack[i][j]) return 1;
    } else if(color==black)
    {
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                if(board[i][j].getPiece()==king && board[i][j].getColor()==black && attacksWhite[i][j]) return 1;
    } else cout<<"????\n";
    return 0;
}