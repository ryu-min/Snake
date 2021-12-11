#include "gamewidget.h"
#include "common.h"

#include <QDebug>

#include <QKeyEvent>
#include <QTimerEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QRandomGenerator>
#include <QMessageBox>

using namespace SnakeGame;

GameWidget::GameWidget(SnakeLevel level, QWidget * parent)
    : QWidget(parent)
    , m_delay(delayByLevel(level))
{
    setFixedSize (DOT_WIDTH * FIELD_WIDTH, DOT_HEIGH * FIELD_HEIGH);
    setWindowTitle(QString("SNAKE"));

    initGame();
}

QSize GameWidget::getSnakeGameSize() const
{
    return QSize(DOT_WIDTH * FIELD_WIDTH, DOT_HEIGH * FIELD_HEIGH);
}

void GameWidget::timerEvent(QTimerEvent *timerEvent)
{
    Q_UNUSED(timerEvent);

    if (m_inGame)
    {
        checkApple();
        moveSnake();
        checkField();
    }
    this->repaint();
}

void GameWidget::keyPressEvent(QKeyEvent *keyEvent)
{
    int key = keyEvent->key();

    if (key == Qt::Key_Left && m_currentDirection != Directions::RIGHT)
    {
        m_currentDirection = Directions::LEFT;
    }
    else if (key == Qt::Key_Right && m_currentDirection != Directions::LEFT)
    {
        m_currentDirection = Directions::RIGHT;
    }
    else if (key == Qt::Key_Up && m_currentDirection != Directions::DOWN)
    {
        m_currentDirection = Directions::UP;
    }
    else if (key == Qt::Key_Down && m_currentDirection != Directions::UP)
    {
        m_currentDirection = Directions::DOWN;
    }
    else if (key == Qt::Key_Escape)
    {
        emit closeGame();
    }
}

void GameWidget::paintEvent(QPaintEvent *paintEvent)
{
    Q_UNUSED(paintEvent);

    QPainter painter(this);

    if (m_inGame)
    {
        painter.setBrush(Qt::red);
        painter.drawEllipse(m_apple.x() * DOT_WIDTH,
                            m_apple.y() * DOT_HEIGH,
                            DOT_WIDTH,
                            DOT_HEIGH);

        for (int i = 0; i < m_dots.size(); i++)
        {
            if (i == 0)
            {
                painter.setBrush(Qt::white);
                painter.drawEllipse(m_dots[i].x() * DOT_WIDTH,
                                    m_dots[i].y() * DOT_HEIGH,
                                    DOT_WIDTH,
                                    DOT_HEIGH);

            }
            else
            {
                painter.setBrush(Qt::green);
                painter.drawEllipse(m_dots[i].x() * DOT_WIDTH,
                                    m_dots[i].y() * DOT_HEIGH,
                                    DOT_WIDTH,
                                    DOT_HEIGH);
            }
        }
    }
    else
    {
        gameover();
    }
}

void GameWidget::showEvent(QShowEvent * showEvent)
{
    m_inGame = true;
    QWidget::showEvent(showEvent);
}

void GameWidget::hideEvent(QHideEvent *hideEvent)
{
    m_inGame = false;
    QWidget::hideEvent(hideEvent);
}

void GameWidget::checkField()
{
    if (m_dots.size() >= 4)
    {
        for (int i = 1; i < m_dots.size(); i++)
        {
            if (m_dots[0] == m_dots[i])
            {
                m_inGame = false;
            }
        }
    }

    if (m_dots[0].rx() >= FIELD_WIDTH   ||
        m_dots[0].rx() < 0              ||
        m_dots[0].ry() >= FIELD_HEIGH   ||
        m_dots[0].ry() < 0)
    {
        m_inGame = false;
    }

    if (!m_inGame)
    {
        killTimer(m_timerID);
    }

}

void GameWidget::checkApple()
{
    if (m_apple == m_dots[0])
    {
        m_dots.push_back(QPoint(0, 0));
        gererateApple();
    }
}

void GameWidget::initGame()
{
    m_inGame = true;
    m_currentDirection = RIGHT;

    m_dots.resize(3);
    for (int i = 0; i < m_dots.size(); i++)
    {
        m_dots[i].setX(m_dots.size() - i - 1);
        m_dots[i].setY(0);
    }

    gererateApple();

    m_timerID = startTimer(m_delay);

}

void GameWidget::gererateApple()
{
    m_apple.setX(QRandomGenerator::global()->generate() % DOT_WIDTH);
    m_apple.setY(QRandomGenerator::global()->generate() % DOT_HEIGH);
}

void GameWidget::moveSnake()
{

    for (int i = m_dots.size() - 1; i > 0; i--)
    {
        m_dots[i] = m_dots[i - 1];
    }

    switch (m_currentDirection)
    {
    case Directions::LEFT:
        m_dots[0].rx() -=1;
        break;
    case Directions::RIGHT:
        m_dots[0].rx() +=1;
        break;
    case Directions::UP:
        m_dots[0].ry() -=1;
        break;
    case Directions::DOWN:
        m_dots[0].ry() +=1;
        break;
    }
}

void GameWidget::gameover()
{
    QMessageBox msg;
    msg.setText(QString("Вы проиграли!"));
    msg.exec();

    initGame();
}
