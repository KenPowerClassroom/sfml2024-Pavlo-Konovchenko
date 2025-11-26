#include <SFML/Graphics.hpp>
#include <time.h>

#include "Board.h"

using namespace sf;

class MousePosition
{
public:
    MousePosition(Vector2i pos, int cellSize)
    {
        x = pos.x / cellSize;
        y = pos.y / cellSize;
    }
    int getX() { return x; }
    int getY() { return y; }

private:
    int x;
    int y;
};

void inputHandler(RenderWindow& app, Board& board, MousePosition mousepos);
void draw(RenderWindow& app, Board& board, Sprite sprite);

int minesweeper()
{
    srand(time(0));

    RenderWindow app(VideoMode(400, 400), "Minesweeper!");
    Board board;

    Texture texture;
    texture.loadFromFile("images/minesweeper/tiles.jpg");
    Sprite sprite(texture);
    
    //
    // Game loop
    //
    while (app.isOpen())
    {
        MousePosition mousepos(Mouse::getPosition(app), board.getCellSize());

        inputHandler(app, board, mousepos);
        draw(app, board, sprite);
    }

    return 0;
}

void inputHandler(RenderWindow& app, Board& board, MousePosition mousepos) 
{
    Event event;
    while (app.pollEvent(event))
    {
        if (event.type == Event::Closed)
            app.close();

        // if mouse was pressed open the cell that was pressed
        // or mark it as a flag
        if (event.type == Event::MouseButtonPressed)
            if (event.key.code == Mouse::Left)
            {
                if (board.getHiddenTileValue(mousepos.getX(), mousepos.getY()) == 9)
                {
                    board.clickedOnBomb();
                    break;
                }
                board.revealGrid(mousepos.getX(), mousepos.getY());
            }
            else if (event.key.code == Mouse::Right) board.setFlag(mousepos.getX(), mousepos.getY());
        
    }
}

void draw(RenderWindow& app, Board& board, Sprite sprite)
{
    int cellSize = board.getCellSize();
    app.clear(Color::White);

    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
        {
            if (board.hasClickedOnBomb()) board.revealGrid(i, j);;
            sprite.setTextureRect(IntRect(board.getShownTileValue(i, j) * cellSize, 0, cellSize, cellSize));
            sprite.setPosition(i * cellSize, j * cellSize);
            app.draw(sprite);
        }

    app.display();
}
