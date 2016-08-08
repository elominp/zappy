#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMovie>
#include <QtMultimedia/QSound>
#include <QMouseEvent>
#include <QPoint>
#include <QTimer>

namespace Ui {
class Widget;
}

class Launcher : public QWidget
{
    Q_OBJECT

public:
    explicit Launcher(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *event);
    ~Launcher();

private:
    Ui::Widget *ui;
    QMovie *movie;
    QSound *sound;
    QTimer *timer;
    int timeout;

    void shop();
    void play();

private slots:
    void onClick(QPoint const &pos);
    void stopIntro(int frame);
    void wakeUp();

signals:
    void mousePressed(QPoint const &pos);
};

#endif // WIDGET_H
