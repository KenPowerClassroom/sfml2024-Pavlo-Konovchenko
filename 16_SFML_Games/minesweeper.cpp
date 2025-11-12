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
        for (int i = 1; i <= 10; i++)
            for (int j = 1; j <= 10; j++)
            {
                shownGrid[i][j] = TileState::ClosedTile;
                if (rand() % 5 == 0)  grid[i][j] = TileState::Bomb;
                else grid[i][j] = TileState::Empty;
            }

        for (int i = 1; i <= 10; i++)
            for (int j = 1; j <= 10; j++)
            {
                int n = 0;
                if (grid[i][j] == TileState::Bomb) continue;
                if (grid[i + 1][j] == TileState::Bomb) n++;
                if (grid[i][j + 1] == TileState::Bomb) n++;
                if (grid[i - 1][j] == TileState::Bomb) n++;
                if (grid[i][j - 1] == TileState::Bomb) n++;
                if (grid[i + 1][j + 1] == TileState::Bomb) n++;
                if (grid[i - 1][j - 1] == TileState::Bomb) n++;
                if (grid[i - 1][j + 1] == TileState::Bomb) n++;
                if (grid[i + 1][j - 1] == TileState::Bomb) n++;
                grid[i][j] = static_cast<TileState> (n);
            }
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
private:
    TileState grid[12][12];
    TileState shownGrid[12][12];
};

int minesweeper()
{
    srand(time(0));

    RenderWindow app(VideoMode(400, 400), "Minesweeper!");

    int w=32;
    Board board;

    Texture t;
    t.loadFromFile("images/minesweeper/tiles.jpg");
    Sprite s(t);
    
    //
    // Game loop
    //
    while (app.isOpen())
    {
        Vector2i pos = Mouse::getPosition(app);
        // Divide by cingular cell sprite size
        // to get which cell we are currently clicking
        int x = pos.x/w;
        int y = pos.y/w;

        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();

            // if mouse was pressed open the cell that was pressed
            // or mark it as a flag
            if (e.type == Event::MouseButtonPressed)
              if (e.key.code == Mouse::Left) board.revealGrid(x, y);
              else if (e.key.code == Mouse::Right) board.setFlag(x, y);
        }


        //
        // Draw
        //
        app.clear(Color::White);

        for (int i=1;i<=10;i++)
         for (int j=1;j<=10;j++)
          {
           if (board.getTileValue(x, y) == 9) board.revealGrid(i, j);;
           s.setTextureRect(IntRect(board.getTileValue(i, j)*w,0,w,w));
           s.setPosition(i*w, j*w);
           app.draw(s);
          }

        app.display();
    }

    return 0;
}
