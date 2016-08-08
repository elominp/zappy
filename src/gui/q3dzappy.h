#ifndef Q3DZAPPY_H
#define Q3DZAPPY_H

#include <QWidget>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QTimerEvent>
#include <QWheelEvent>
#include <irrlicht.h>

class Q3DZappy : public QWidget
{
    Q_OBJECT
public:
    explicit Q3DZappy(QWidget *parent = 0);
    ~Q3DZappy();

private:
    irr::video::E_DRIVER_TYPE _driverType;
    irr::IrrlichtDevice *_device;

    void setupScene();
    void init();
    void updateIrrlicht();
    void sendMouseEventToIrrlicht(QMouseEvent *, bool);

public slots:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);

private slots:
    void timerEvent(QTimerEvent *);
};

#endif // Q3DZAPPY_H
