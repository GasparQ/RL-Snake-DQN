#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <QObject>

#include <vector>
#include <list>
#include <unordered_map>

class SnakeGame : public QObject
{
    Q_OBJECT

public:
    enum CellType {
        EMPTY,
        WALL,
        SNAKE,
        APPLE
    };

    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    using SnakeGrid = std::vector<CellType>;

private:
    struct Position {
        size_t x;
        size_t y;
    };

    struct Vector {
        long x;
        long y;
    };

    static const std::unordered_map<Direction, Vector> Directions;

public:
    SnakeGame();

public:
    void initGame(size_t width, size_t height);
    void updateGrid();
    void setSnakeDirection(Direction direction);

public:
    const SnakeGrid &getGrid() const;
    size_t getWidth() const;
    size_t getHeight() const;

private:
    void setCellValue(size_t x, size_t y, CellType value);
    void setCellValue(size_t i, CellType value);
    CellType getCellValue(size_t x, size_t y) const;
    void setSnakeDirection(Vector const &direction);
    Position getNextPos() const;
    void randomizeApple();

signals:
    void gridUpdated(SnakeGrid const &grid);
    void gameStarted(SnakeGrid const &grid);
    void gameOver(size_t score);

private:
    SnakeGrid    m_grid;
    size_t  m_width;
    size_t  m_height;

private:
    Position *m_snakeHead;
    Position *m_snakeTail;
    std::list<Position> m_snakeBody;
    size_t m_snakeSize;
    Vector m_snakeDirection;
};

#endif // SNAKEGAME_H
