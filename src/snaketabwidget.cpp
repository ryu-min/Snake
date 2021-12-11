#include "snaketabwidget.h"

#include <QDebug>
#include <QTabBar>
#include <QKeyEvent>

SnakeGame::SnakeTabWidget::SnakeTabWidget(QWidget *parent)
    : QTabWidget(parent)
    , m_snakeStartWidget(new StartGameWidget(this))
    , m_snakeGameWidget(new GameWidget(SnakeLevel::EASY, this))
{
    addTab(m_snakeStartWidget, "Start");
    addTab(m_snakeGameWidget, "Snake");
    tabBar()->hide();

    connect(m_snakeStartWidget, &StartGameWidget::startGame,
            this, &SnakeTabWidget::startGame);

    connect(m_snakeGameWidget, &GameWidget::closeGame,
            this, &SnakeTabWidget::stopGame);

    setCurrentIndex(indexOf(m_snakeStartWidget));
}

void SnakeGame::SnakeTabWidget::startGame(SnakeGame::SnakeLevel level)
{
    removeTab(indexOf(m_snakeGameWidget));
    delete m_snakeGameWidget;
    m_snakeGameWidget = new GameWidget(level, this);

    connect(m_snakeGameWidget, &GameWidget::closeGame,
            this, &SnakeTabWidget::stopGame);

    connect(m_snakeStartWidget, &StartGameWidget::continueGame,
            this, &SnakeTabWidget::continueGame);

    addTab(m_snakeGameWidget, "Snake");
    resize(m_snakeGameWidget->getSnakeGameSize());
    setCurrentIndex(indexOf(m_snakeGameWidget));
}

void SnakeGame::SnakeTabWidget::continueGame()
{
    resize(m_snakeGameWidget->getSnakeGameSize());
    setCurrentIndex(indexOf(m_snakeGameWidget));
}

void SnakeGame::SnakeTabWidget::stopGame()
{
    setCurrentIndex(indexOf(m_snakeStartWidget));
}




