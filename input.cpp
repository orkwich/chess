#include "board.hpp"
using namespace sf;

void Board::input()
{
    Event event;
    int zoom=1; //can be used later
    while(window.pollEvent(event))
    {
        if(event.type==Event::Closed) window.close();
        if(event.type==Event::KeyPressed)
            if(Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
        if(event.type==Event::MouseButtonPressed && !mat)
        {
            Vector2i locMousePos=Mouse::getPosition(window);
            Vector2f tmp;
            if(Mouse::isButtonPressed(Mouse::Left))
            {
                int fieldSize=(resolution.x/zoom)/8;
                int sidePanelWidth=(800-(resolution.x/zoom))/2;
                Vector2i origin=Vector2i(((int(locMousePos.x-sidePanelWidth)-(int(locMousePos.x-sidePanelWidth)%fieldSize))/fieldSize),((int(locMousePos.y-sidePanelWidth)-(int(locMousePos.y-sidePanelWidth)%fieldSize))/fieldSize));
                while(Mouse::isButtonPressed(Mouse::Left) && locMousePos.x>=sidePanelWidth && locMousePos.x<=RES-sidePanelWidth && locMousePos.y>=sidePanelWidth && locMousePos.y<=RES-sidePanelWidth)
                {
                    tmp=Vector2f(Mouse::getPosition(window));
                    board[origin.x][origin.y].setPosition(Vector2i((tmp.x-sidePanelWidth)*zoom,(tmp.y-sidePanelWidth)*zoom));
                    draw();
                }
                tmp=Vector2f(origin.x*fieldSize+fieldSize/2,origin.y*fieldSize+fieldSize/2);
                board[origin.x][origin.y].setPosition(Vector2i(tmp.x*zoom,tmp.y*zoom));
                locMousePos=Mouse::getPosition(window);
                
                Vector2i from=Vector2i(origin.x,origin.y);
                Vector2i to=Vector2i(((int(locMousePos.x-sidePanelWidth)-(int(locMousePos.x-sidePanelWidth)%fieldSize))/fieldSize),((int(locMousePos.y-sidePanelWidth)-(int(locMousePos.y-sidePanelWidth)%fieldSize))/fieldSize));
                
                tryMove(from,to,1);

                board[origin.x][origin.y].fix();
                draw();
            }
        }
    }
}