#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImage>
#include <QHBoxLayout>
#include <QLabel>

#include "snakegame.h"

class SnakeWidget : public QWidget
{
    Q_OBJECT

public:
    enum Action {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        NONE
    };

public:
    SnakeWidget(QWidget *parent = 0);
    ~SnakeWidget();

public:
    void init();
    void step(Action action);
    const SnakeGame::SnakeGrid &getObservation();
    bool isSnakeGameOver();


private slots:
    void repaint();

private:
    void keyPressEvent(QKeyEvent *event);

private:
    QHBoxLayout m_layout;
    QLabel m_label;
    QImage m_image;
    SnakeGame   m_game;
};

#endif // WIDGET_H
