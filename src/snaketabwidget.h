#ifndef SNAKETABWIDGET_H
#define SNAKETABWIDGET_H

#include <QTabWidget>

#include "gamewidget.h"
#include "startgamewidget.h"

namespace SnakeGame
{
    class SnakeTabWidget : public QTabWidget
    {
        Q_OBJECT
    public:
        explicit SnakeTabWidget(QWidget * parent = nullptr);

    private slots:
        void startGame(SnakeLevel level);
        void continueGame();
        void stopGame();

    private:
        StartGameWidget * m_snakeStartWidget;
        GameWidget      * m_snakeGameWidget;
    };
}
#endif // SNAKETABWIDGET_H
