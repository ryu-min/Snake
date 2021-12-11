#ifndef STARTGAMEWIDGET_H
#define STARTGAMEWIDGET_H

#include <QWidget>

#include "common.h"

namespace Ui {
    class StartGameWidget;
}

namespace SnakeGame
{
    class StartGameWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit StartGameWidget(QWidget *parent = nullptr);
        ~StartGameWidget();

    signals:
        void startGame(SnakeLevel level);
        void continueGame();

    private slots:
        void on_m_difficultyComboBox_currentIndexChanged(const QString &arg1);

        void on_pushButton_clicked();

        void on_pushButton_2_clicked();

    private:
        SnakeLevel m_level;

    private:
        Ui::StartGameWidget *ui;
    };
}
#endif // STARTGAMEWIDGET_H
