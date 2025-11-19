#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

enum class TileState
{
    Empty,
    OneBomb,
    TwoBombs,
    ThreeBombs,
    FourBombs,
    FiveBombs,
    SixBombs,
    SevenBombs,
    EightBombs,
    Bomb,
    ClosedTile,
    Flagged
};

class Board
{
public:
    Board()
    {
        randomizeBombs();
        countBombs();
    };

    void revealGrid(int t_x, int t_y)
    {
        shownGrid[t_x][t_y] = grid[t_x][t_y];
    }
    void setFlag(int t_x, int t_y)
    {
        shownGrid[t_x][t_y] = TileState::Flagged;
    }
    int getTileValue(int t_x, int t_y)
    {
        return static_cast<int> (shownGrid[t_x][t_y]);
    }
    int getCellSize() { return cellSize; }
private:
    TileState grid[12][12];
    TileState shownGrid[12][12];
    int cellSize = 32;

    void randomizeBombs()
    {
        for (int i = 1; i <= 10; i++)
            for (int j = 1; j <= 10; j++)
            {
                shownGrid[i][j] = TileState::ClosedTile;
                if (rand() % 5 == 0)  grid[i][j] = TileState::Bomb;
                else grid[i][j] = TileState::Empty;
            }
    }
    void countBombs()
    {
        for (int i = 1; i <= 10; i++)
            for (int j = 1; j <= 10; j++)
            {
                if (grid[i][j] == TileState::Bomb) continue;

                int n = 0;
                int iCounter = -1;
                int jCounter = -1;
                for (int bombCheck = 0; bombCheck <= 8; bombCheck++)
                {
                    if (bombCheck % 3 == 0 && bombCheck != 0)
                    {
                        iCounter++;
                        jCounter = -1;
                    }
                    if (grid[i + iCounter][j + jCounter] == TileState::Bomb)
                    {
                        n++;
                    }
                    jCounter++;
                }
                grid[i][j] = static_cast<TileState> (n);
            }
    }
};

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

void inputHandler(RenderWindow& app, Board& board, MousePosition mouse);
void draw(RenderWindow& app, Sprite sprite, Board& board, MousePosition mouse);

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
        draw(app, sprite, board, mousepos);
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
            if (event.key.code == Mouse::Left) board.revealGrid(mousepos.getX(), mousepos.getY());
            else if (event.key.code == Mouse::Right) board.setFlag(mousepos.getX(), mousepos.getY());
    }
}

void draw(RenderWindow& app, Sprite sprite, Board& board, MousePosition mousepos)
{
    int cellSize = board.getCellSize();
    app.clear(Color::White);

    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
        {
            if (board.getTileValue(mousepos.getX(), mousepos.getY()) == 9) board.revealGrid(i, j);;
            sprite.setTextureRect(IntRect(board.getTileValue(i, j) * cellSize, 0, cellSize, cellSize));
            sprite.setPosition(i * cellSize, j * cellSize);
            app.draw(sprite);
        }

    app.display();
}
