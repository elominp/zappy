#include <iostream>
#include <QMessageBox>
#include "launcher.h"
#include "ui_widget.h"
#include "zappyui.h"

Launcher::Launcher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    movie = new QMovie("intro.gif");
    ui->intro->setMovie(movie);
    movie->setSpeed(250);
    movie->start();
    sound = new QSound("sound.wav");
    sound->play();
    timeout = 20000;
    timer = new QTimer();
    timer->start(timeout);

    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    this->setWindowFlags(Qt::CustomizeWindowHint);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    QObject::connect(this, SIGNAL(mousePressed(QPoint)), this, SLOT(onClick(QPoint)));
    QObject::connect(movie, SIGNAL(frameChanged(int)), this, SLOT(stopIntro(int)));
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(wakeUp()));
}

void Launcher::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    emit mousePressed(pos);
}

void Launcher::onClick(const QPoint &pos)
{
    if (pos.x() >= 105 && pos.x() <= 280 && pos.y() >= 365 && pos.y() <= 405)
        shop();
    else if (pos.x() >= 310 && pos.x() <= 485 && pos.y() >= 365 && pos.y() <= 405)
        play();
}

void Launcher::stopIntro(int frame)
{
    if (frame >= (movie->frameCount() - 1))
        movie->stop();
}

void Launcher::wakeUp()
{
    movie->stop();
    sound->stop();
    movie->start();
    sound->play();
    timer->start(timeout);
}

void Launcher::shop()
{
    QMessageBox::information(this, "Zappy Shop Status", "Sorry, the shop isn't available yet.");
}

void Launcher::play()
{
    this->hide();
    timer->stop();
    movie->stop();
    sound->stop();
    ZappyUI *gui = new ZappyUI;
    gui->show();
    this->destroy(true, false);
}

Launcher::~Launcher()
{
    delete ui;
}
