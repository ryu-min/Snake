#include "startgamewidget.h"
#include "ui_startgamewidget.h"

#include <QStringList>
#include <QPixmap>

using namespace SnakeGame;

StartGameWidget::StartGameWidget(QWidget *parent)
    : QWidget(parent)
    , m_level(SnakeLevel::EASY)
    , ui(new Ui::StartGameWidget)
{
    ui->setupUi(this);

    ui->m_nakeIconLabel->setPixmap(QPixmap(":/images/snake.png"));

    ui->m_difficultyComboBox->addItems(QStringList() << levelToString(SnakeLevel::EASY)
                                                     << levelToString(SnakeLevel::MEDIUM)
                                                     << levelToString(SnakeLevel::HARD));
}

StartGameWidget::~StartGameWidget()
{
    delete ui;
}

void StartGameWidget::on_m_difficultyComboBox_currentIndexChanged(const QString & difficulty)
{
    m_level = stringToLevel(difficulty);
}

void SnakeGame::StartGameWidget::on_pushButton_clicked()
{
    emit startGame(m_level);
}

void SnakeGame::StartGameWidget::on_pushButton_2_clicked()
{
    emit continueGame();
}
