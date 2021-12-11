#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QSize>

#include "common.h"

namespace SnakeGame
{

    class GameWidget : public QWidget
    {
        Q_OBJECT
    public:
        GameWidget(SnakeLevel level, QWidget * parent = nullptr);
        QSize getSnakeGameSize() const;

    protected:
        void timerEvent     (QTimerEvent * timerEvent)  override;
        void keyPressEvent  (QKeyEvent * keyEvent)      override;
        void paintEvent     (QPaintEvent * paintEvent)  override;
        void showEvent      (QShowEvent *event)         override;
        void hideEvent      (QHideEvent *event)         override;

    signals:
        void closeGame();

    private:

       enum Directions
       {
           LEFT,
           RIGHT,
           UP,
           DOWN
       };
       
    private:
       void gererateApple();
       void moveSnake();
       void checkField();
       void checkApple();
       void gameover();
       void initGame();
    
    private:
       bool             m_inGame;
       Directions       m_currentDirection;
       QPoint           m_apple;
       QVector<QPoint>  m_dots;
       int              m_timerID;
       int              m_delay;
    };

}
#endif // GAME_H
