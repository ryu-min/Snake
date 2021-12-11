#include <QApplication>

#include "snaketabwidget.h"

int main(int argc, char ** argv)
{
    QApplication app (argc, argv);
    SnakeGame::SnakeTabWidget start;
    start.resize(460, 280);
    start.show();

    return app.exec();
}
