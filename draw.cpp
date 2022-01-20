#include "board.hpp"

void Board::draw()
{
    window.draw(background);
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++) window.draw(board[i][j]);
    }
    window.display();
    window.clear(Color::Black);
}