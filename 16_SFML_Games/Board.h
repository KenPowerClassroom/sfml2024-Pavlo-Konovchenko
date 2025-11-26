#pragma once

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
    }

    Board(int t_grid[12][12])
    {
        for (int i = 1; i <= 10; i++)
            for (int j = 1; j <= 10; j++)
            {
                shownGrid[i][j] = TileState::ClosedTile;
                grid[i][j] = static_cast<TileState>(t_grid[i][j]);
            }
        countBombs();
    }

    void revealGrid(int t_x, int t_y)
    {
        shownGrid[t_x][t_y] = grid[t_x][t_y];
    }
    void setFlag(int t_x, int t_y)
    {
        shownGrid[t_x][t_y] = TileState::Flagged;
    }
    int getShownTileValue(int t_x, int t_y)
    {
        return static_cast<int> (shownGrid[t_x][t_y]);
    }
    int getHiddenTileValue(int t_x, int t_y)
    {
        return static_cast<int> (grid[t_x][t_y]);
    }
    int getCellSize() { return cellSize; }
    void clickedOnBomb() { blewUp = true; }
    bool hasClickedOnBomb() { return blewUp; }
private:
    TileState grid[12][12];
    TileState shownGrid[12][12];
    int cellSize = 32;
    bool blewUp = false;

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