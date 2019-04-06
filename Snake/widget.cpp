#include <QObject>
#include <QPainter>
#include <QKeyEvent>

#include <QDebug>

#include "widget.h"

SnakeWidget::SnakeWidget(QWidget *parent)
    : QWidget(parent)
{
    connect(&m_game, SIGNAL(gridUpdated()),
            this, SLOT(repaint()));
    connect(&m_game, SIGNAL(gameStarted()),
            this, SLOT(repaint()));
}

SnakeWidget::~SnakeWidget()
{

}

void SnakeWidget::init()
{
    m_image = QImage(600, 600, QImage::Format::Format_RGB32);
    m_image.fill(QColor("#000000"));
    m_layout.addWidget(&m_label);
    setLayout(&m_layout);

    m_game.initGame(60, 60);
}

void SnakeWidget::step(Action action)
{
    if (action != Action::NONE) {
        m_game.setSnakeDirection(static_cast<SnakeGame::Direction>(action));
    }
    m_game.updateGrid();
}

void SnakeWidget::repaint()
{
    QPainter painter(&m_image);
    size_t i = 0;
    size_t boxWidth = m_image.width() / m_game.getWidth();
    size_t boxHeight = m_image.height() / m_game.getHeight();

    for (SnakeGame::CellType cell : m_game.getGrid()) {
        size_t x = i % m_game.getWidth();
        size_t y = i / m_game.getWidth();

        switch (cell) {
        case SnakeGame::CellType::WALL:
            painter.setBrush(QBrush(QColor("#f4773d")));
            break;
        case SnakeGame::CellType::APPLE:
            painter.setBrush(QBrush(QColor("#f43d3d")));
            break;
        case SnakeGame::CellType::EMPTY:
            painter.setBrush(QBrush(QColor("#000000")));
            break;
        case SnakeGame::CellType::SNAKE:
            painter.setBrush(QBrush(QColor("#58f43d")));
            break;
        }

        painter.drawRect(QRect(x * boxWidth, y * boxHeight, boxWidth, boxHeight));
        i++;
    }

    m_label.setPixmap(QPixmap::fromImage(m_image));
}

void SnakeWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        step(Action::UP);
        break;
    case Qt::Key_Down:
        step(Action::DOWN);
        break;
    case Qt::Key_Left:
        step(Action::LEFT);
        break;
    case Qt::Key_Right:
        step(Action::RIGHT);
        break;
    default:
        step(Action::NONE);
        break;
    }
}
