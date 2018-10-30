#include "gamewindow.hh"
#include "hexgraphicsitem.hh"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::init()
{
    auto scene = new QGraphicsScene;
    ui->boardView->setScene(scene);
    scene->addItem(new HexGraphicsItem());
}
