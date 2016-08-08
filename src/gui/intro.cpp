#include <iostream>
#include "intro.h"
#include "ui_intro.h"

Intro::Intro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Intro)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    player = new QMediaPlayer;
    video = new QVideoWidget;
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile("intro.avi"));
    player->setVideoOutput(video);
    player->setPlaylist(playlist);
    this->layout()->addWidget(video);
    isExitable = false;
    video->show();
    playlist->setCurrentIndex(0);
    QObject::connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
                     this, SLOT(onIntroTerminated(QMediaPlayer::MediaStatus)));
    player->play();
    std::cerr << player->mediaStatus() << std::endl;
}

Intro::~Intro()
{
    delete ui;
    delete player;
    delete video;
    delete playlist;
}

void Intro::allowExit()
{
    isExitable = true;
}

void Intro::onClick()
{
    if (isExitable)
        this->destroy();
}

void Intro::onIntroTerminated(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia)
        this->destroy();
}

void Intro::stop()
{
    player->stop();
    this->destroy();
}
