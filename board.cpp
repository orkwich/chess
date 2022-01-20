#include "board.hpp"

Board::Board(Texture *background, Texture *pawnWhite, Texture *pawnBlack, Texture *rookWhite, Texture *rookBlack, Texture *knightWhite, Texture *knightBlack, Texture *bishopWhite, Texture *bishopBlack, Texture *queenWhite, Texture *queenBlack, Texture *kingWhite, Texture *kingBlack)
{
    this->queenTextureWhite = queenWhite;
    this->queenTextureBlack = queenBlack;
    this->background.setTextureRect(IntRect(0,0,800,800));
    this->background.setTexture(*background);
    window.create(VideoMode(resolution.x,resolution.y),"",Style::None);
    window.clear(Color::Black);
    window.setFramerateLimit(FPS);
    for(int i=0;i<8;i++) board[i][1] = Pawn(pawnBlack,Vector2i(i,1),black);
    for(int i=0;i<8;i++) board[i][6] = Pawn(pawnWhite,Vector2i(i,6),white);

    board[0][0] = Rook(rookBlack,Vector2i(0,0),black);
    board[7][0] = Rook(rookBlack,Vector2i(7,0),black);
    board[1][0] = Knight(knightBlack,Vector2i(1,0),black);
    board[6][0] = Knight(knightBlack,Vector2i(6,0),black);
    board[2][0] = Bishop(bishopBlack,Vector2i(2,0),black);
    board[5][0] = Bishop(bishopBlack,Vector2i(5,0),black);
    board[3][0] = Queen(queenBlack,Vector2i(3,0),black);
    board[4][0] = King(kingBlack, Vector2i(4,0),black);

    board[0][7] = Rook(rookWhite,Vector2i(0,7),white);
    board[7][7] = Rook(rookWhite,Vector2i(7,7),white);
    board[1][7] = Knight(knightWhite,Vector2i(1,7),white);
    board[6][7] = Knight(knightWhite,Vector2i(6,7),white);
    board[2][7] = Bishop(bishopWhite,Vector2i(2,7),white);
    board[5][7] = Bishop(bishopWhite,Vector2i(5,7),white);
    board[3][7] = Queen(queenWhite,Vector2i(3,7),white);
    board[4][7] = King(kingWhite,Vector2i(4,7),white);

    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            attacksWhite[i][j]=0;
            attacksBlack[i][j]=0;
        }
    attacksUpdate();

    mat=0;
    moveCount=0;
    whiteScore=0;
    blackScore=0;
}

void Board::fix()
{
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++) board[i][j].fix();
}

bool Board::capture(Vector2i from, Vector2i to, bool isEnPassant, bool doCommit)
{
    if(from.x!=to.x || from.y!=to.y)
    {
        int y=to.y;
        if(isEnPassant) y=from.y;
        enum color color = board[from.x][from.y].getColor();
        Piece pieceCaptured = Piece(board[to.x][y].getTexture(), Vector2i(to.x,y), board[to.x][y].getColor(), board[to.x][y].getPiece());
        pieceCaptured.didMove = board[to.x][y].didMove;
        board[to.x][to.y] = Piece(board[from.x][from.y].getTexture(), Vector2i(to.x,to.y), board[from.x][from.y].getColor(), board[from.x][from.y].getPiece());
        board[to.x][to.y].didMove=1;
        bool lastPieceMovedDidMove = board[from.x][from.y].didMove;
        board[from.x][from.y].discombobulate();
        if(isEnPassant) board[to.x][from.y].discombobulate();
        if(isCheck(color))
        {
            board[from.x][from.y] = Piece(board[to.x][to.y].getTexture(), Vector2i(from.x,from.y), board[to.x][to.y].getColor(), board[to.x][to.y].getPiece());
            board[from.x][from.y].didMove=lastPieceMovedDidMove;
            board[to.x][y] = Piece(pieceCaptured.getTexture(), Vector2i(to.x,y), pieceCaptured.getColor(), pieceCaptured.getPiece());
            board[to.x][y].didMove = pieceCaptured.didMove;
            return 0;
        }
        if(!doCommit)
        {
            board[from.x][from.y] = Piece(board[to.x][to.y].getTexture(), Vector2i(from.x,from.y), board[to.x][to.y].getColor(), board[to.x][to.y].getPiece());
            board[from.x][from.y].didMove=lastPieceMovedDidMove;
            board[to.x][y] = Piece(pieceCaptured.getTexture(), Vector2i(to.x,y), pieceCaptured.getColor(), pieceCaptured.getPiece());
            board[to.x][y].didMove = pieceCaptured.didMove;
        }
        return 1;
    }
    return 0;
}

bool Board::tryCapture(Vector2i from, Vector2i to, bool doCommit)
{
    if(doCommit) scoreUpdate(from,to);
    enum color color = board[to.x][to.y].getColor();
    enum piece_value piece = board[to.x][to.y].getPiece();
    if(capture(from,to,0,doCommit))
    {
        if(doCommit) updateStuffAfterMove();
        return 1;
    }
    if(color==white && doCommit) blackScore-=piece;
    if(color==black && doCommit) whiteScore-=piece;
    return 0;
}

bool Board::isCoordGood(Vector2i coord)
{
    return !(coord.x<0 || coord.y<0 || coord.x>7 || coord.y>7);
}

void Board::enPassantUpdate(enum color color)
{
    int j=4;
    if(color==black) j--;
    for(int i=0;i<8;i++) board[i][j].canBeEnPassaned=0;
}

void Board::updateStuffAfterMove()
{
    moveCount++;
    if(moveCount%2==1) //white did move
    {
        enPassantUpdate(black);
        tryPawnPromotion(white);
        if(isMat(black))
        {
            mat=1;
            cout<<"Checkmate white wins\n";
        }
    } else //black did move
    {
        enPassantUpdate(white);
        tryPawnPromotion(black);
        if(isMat(white))
        {
            mat=1;
            cout<<"Checkmate black wins\n";
        }
    }
}

void Board::tryPawnPromotion(enum color color)
{
    int line=0;
    Texture *tx = queenTextureWhite;
    if(color==black)
    {
        line=7;
        tx=queenTextureBlack;
    }
    for(int i=0;i<8;i++)
        if(board[i][line].getPiece()==pawn)
        {
            board[i][line] = Queen(tx,Vector2i(i,line),color);
            board[i][line].didMove=1;
        }
}

void Board::scoreUpdate(Vector2i from, Vector2i to)
{
    if(board[from.x][from.y].getColor()==white) whiteScore+=board[to.x][to.y].getPiece();
    if(board[from.x][from.y].getColor()==black) blackScore+=board[to.x][to.y].getPiece();
}

void Board::enPassantCheck()
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++) cout<<board[j][i].canBeEnPassaned<<' ';
        cout<<'\n';
    }
    cout<<'\n';
}

bool Board::tryMove(Vector2i from, Vector2i to, bool doCommit)
{
    if(!isCoordGood(from) || !isCoordGood(to)) return 0;
    if(moveCount%2==0 && board[from.x][from.y].getColor()==black) return 0;
    if(moveCount%2==1 && board[from.x][from.y].getColor()==white) return 0;
    if(board[from.x][from.y].getColor()==board[to.x][to.y].getColor()) return 0;
    piece_value piece = board[from.x][from.y].getPiece();
    switch(piece)
    {
        case non:
        {
            return 0;
        }
        case pawn:
        {
            return tryPawnMove(from,to,doCommit);
        }
        case knight:
        {
            return tryKnightMove(from,to,doCommit);
        }
        case bishop:
        {
            return tryBishopMove(from,to,doCommit);
        }
        case rook:
        {
            return tryRookMove(from,to,doCommit);
        }
        case queen:
        {
            return tryQueenMove(from,to,doCommit);
        }
        case king:
        {
            if(moveCount%2==0)
            {
                return tryKingMove(from,to,attacksBlack,doCommit);
            }
            if(moveCount%2==1)
            {
                return tryKingMove(from,to,attacksWhite,doCommit);
            }
            break;
        }
    }
}

bool Board::isMat(enum color color)
{
    if(isCheck(color))
    {
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(board[i][j].getColor()==color)
                {
                    enum piece_value piece = board[i][j].getPiece();
                    vector<Vector2i> v;
                    switch(piece)
                    {
                        case non:
                        {
                            break;
                        }
                        case pawn:
                        {
                            v=pawnMoves(Vector2i(i,j));
                            break;
                        }
                        case knight:
                        {
                            v=knightMoves(Vector2i(i,j));
                            break;
                        }
                        case bishop:
                        {
                            v=bishopMoves(Vector2i(i,j));
                            break;
                        }
                        case rook:
                        {
                            v=rookMoves(Vector2i(i,j));
                            break;
                        }
                        case queen:
                        {
                            v=queenMoves(Vector2i(i,j));
                            break;
                        }
                        case king:
                        {
                            v=kingMoves(Vector2i(i,j));
                            break;
                        }
                    }
                    for(int ii=0;ii<v.size();ii++)
                        if(tryMove(Vector2i(i,j), Vector2i(v[ii].x,v[ii].y),0)) return 0;
                }
            }
        }
    } else return 0;
    return 1;
}

void Board::run()
{
    while(window.isOpen())
    {
        draw();
        input();
    }
}