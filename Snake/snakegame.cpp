#include <QRandomGenerator>

#include "snakegame.h"

const std::unordered_map<SnakeGame::Direction, SnakeGame::Vector> SnakeGame::Directions = {
    { SnakeGame::Direction::UP, { -1, 0 } },
    { SnakeGame::Direction::DOWN, { 1, 0 } },
    { SnakeGame::Direction::LEFT, { 0, -1 } },
    { SnakeGame::Direction::RIGHT, { 0, 1 } }
};

SnakeGame::SnakeGame()
{

}

void SnakeGame::initGame(size_t width, size_t height)
{
    //realloc map
    m_grid.clear();
    m_grid.assign(width * height, CellType::EMPTY);
    m_width = width;
    m_height = height;

    //write walls
    for (size_t x = 0; x < width; x++) {
        setCellValue(x, 0, CellType::WALL);
        setCellValue(x, height - 1, CellType::WALL);
    }

    for (size_t y = 0; y < height; y++) {
        setCellValue(0, y, CellType::WALL);
        setCellValue(width - 1, y, CellType::WALL);
    }

    //setup snake
    m_snakeSize = 3;
    setSnakeDirection(Directions.at(Direction::RIGHT));
    m_snakeBody.push_back(Position {
                              (width - m_snakeSize) / 2,
                              height / 2
                          });
    for (size_t i = 0; i < m_snakeSize - 1; i++) {
        m_snakeBody.push_back(Position {
                                  m_snakeBody.back().x + 1,
                                  m_snakeBody.back().y
                              });
    }
    m_snakeHead = &m_snakeBody.front();
    m_snakeTail = &m_snakeBody.back();

    for (Position const &curr : m_snakeBody) {
        setCellValue(curr.x, curr.y, CellType::SNAKE);
    }

    randomizeApple();

    emit gameStarted();
}

void SnakeGame::updateGrid()
{
    Position nextPos = getNextPos();
    CellType nextCell = getCellValue(nextPos.x, nextPos.y);

    setCellValue(nextPos.x, nextPos.y, CellType::SNAKE);
    m_snakeBody.push_front(nextPos);
    m_snakeHead = &m_snakeBody.front();

    switch (nextCell) {
    case CellType::APPLE:
        m_snakeSize++;
        randomizeApple();
        break;
    case CellType::SNAKE:
    case CellType::WALL:
        emit gameOver(m_snakeSize);
        break;
    default:
        setCellValue(m_snakeTail->x, m_snakeTail->y, CellType::EMPTY);
        m_snakeBody.pop_back();
        m_snakeTail = &m_snakeBody.back();
        break;
    }

    emit gridUpdated();
}

void SnakeGame::setSnakeDirection(SnakeGame::Direction direction)
{
    const Vector &targetDirection = SnakeGame::Directions.at(direction);

    if (m_snakeDirection.x + targetDirection.x == 0
        || m_snakeDirection.y + targetDirection.y == 0)
        return;

    setSnakeDirection(targetDirection);
}

const SnakeGame::SnakeGrid &SnakeGame::getGrid() const
{
    return m_grid;
}

size_t SnakeGame::getWidth() const
{
    return m_width;
}

size_t SnakeGame::getHeight() const
{
    return m_height;
}

void SnakeGame::setCellValue(size_t x, size_t y, SnakeGame::CellType value)
{
    setCellValue(x + y * m_width, value);
}

void SnakeGame::setCellValue(size_t i, SnakeGame::CellType value)
{
    m_grid[i] = value;
}

SnakeGame::CellType SnakeGame::getCellValue(size_t x, size_t y) const
{
    return m_grid[x + y * m_width];
}

void SnakeGame::setSnakeDirection(const SnakeGame::Vector &direction)
{
    m_snakeDirection.x = direction.x;
    m_snakeDirection.y = direction.y;
}

SnakeGame::Position SnakeGame::getNextPos() const
{
    return Position {
        m_snakeHead->x + m_snakeDirection.x,
        m_snakeHead->y + m_snakeDirection.y
    };
}

void SnakeGame::randomizeApple()
{
    for(;;)
    {
        size_t i = m_width * m_height * QRandomGenerator::global()->generateDouble() - 1;

        if (m_grid[i] == CellType::EMPTY) {
            setCellValue(i, CellType::APPLE);
            return;
        }
    }
}
