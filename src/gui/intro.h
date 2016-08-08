#ifndef INTRO_H
#define INTRO_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaPlaylist>

namespace Ui {
class Intro;
}

class Intro : public QWidget
{
    Q_OBJECT

public:
    explicit Intro(QWidget *parent = 0);
    ~Intro();

public slots:
    void allowExit();
    void onClick();
    void onIntroTerminated(QMediaPlayer::MediaStatus);
    void stop();

private:
    Ui::Intro *ui;
    bool isExitable;
    QMediaPlayer *player;
    QVideoWidget *video;
    QMediaPlaylist *playlist;
};

#endif // INTRO_H
