#include "q3dzappy.h"

Q3DZappy::Q3DZappy(QWidget *parent) : QWidget(parent),
    _device(nullptr),
    _driverType(irr::video::EDT_OPENGL)
{
    init();
}

Q3DZappy::~Q3DZappy()
{
    if (_device != nullptr)
    {
        _device->closeDevice();
        _device->run();
        _device->drop();
    }
}

void Q3DZappy::setupScene()
{
    irr::scene::ISceneManager *manager = _device->getSceneManager();
    irr::scene::ISceneNode *node = manager->addCubeSceneNode();
    node = manager->addSphereSceneNode(20.);
    irr::gui::IGUIEnvironment *gui = _device->getGUIEnvironment();
    gui->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
                        irr::core::rect<irr::s32>(10,10,260,22), true);
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    node->setPosition(irr::core::vector3df(0, 0, 0));
    node = manager->addLightSceneNode(node);
    irr::scene::ICameraSceneNode *camera = manager->addCameraSceneNode();
    camera->setPosition(irr::core::vector3df(100, 100, 0));
    camera->setTarget(irr::core::vector3df(0, 0, 0));
}

void Q3DZappy::init()
{
    irr::SIrrlichtCreationParameters parameters;

    if (_device != nullptr)
        return;
    parameters.DriverType = _driverType;
    parameters.WindowId = (void *)this->winId();
    parameters.WindowSize.Width = this->width();
    parameters.WindowSize.Height = this->height();
    _device = irr::createDeviceEx(parameters);
    this->setAttribute(Qt::WA_OpaquePaintEvent);
    setupScene();
    this->startTimer(0);
}

void Q3DZappy::paintEvent(QPaintEvent *event)
{
    if (_device != nullptr)
        updateIrrlicht();
}

void Q3DZappy::timerEvent(QTimerEvent *event)
{
    if (_device != nullptr)
        updateIrrlicht();
    event->accept();
}

void Q3DZappy::resizeEvent(QResizeEvent *event)
{
    if (_device != nullptr)
    {
        irr::core::dimension2d<uint32_t> size;
        irr::scene::ICameraSceneNode *camera = _device->getSceneManager()->getActiveCamera();

        size.Width = event->size().width();
        size.Height = event->size().height();
        _device->getVideoDriver()->OnResize(size);
        if (camera != nullptr)
            camera->setAspectRatio(size.Height / size.Width);
    }
    QWidget::resizeEvent(event);
}

void Q3DZappy::updateIrrlicht()
{
    irr::video::SColor color(255, 100, 101, 140);

    _device->getTimer()->tick();
    _device->getVideoDriver()->beginScene(true, true, color);
    _device->getSceneManager()->drawAll();
    _device->getGUIEnvironment()->drawAll();
    _device->getVideoDriver()->endScene();
}

void Q3DZappy::sendMouseEventToIrrlicht(QMouseEvent *event, bool clicked)
{
    irr::SEvent irrEvent;

    irrEvent.EventType = irr::EET_MOUSE_INPUT_EVENT;
    switch (event->button())
    {
    case Qt::LeftButton:
        irrEvent.MouseInput.Event = (clicked) ? irr::EMIE_LMOUSE_PRESSED_DOWN : irr::EMIE_LMOUSE_LEFT_UP;
        break;
    case Qt::MidButton:
        irrEvent.MouseInput.Event = (clicked) ? irr::EMIE_MMOUSE_PRESSED_DOWN : irr::EMIE_MMOUSE_LEFT_UP;
        break;
    case Qt::RightButton:
        irrEvent.MouseInput.Event = (clicked) ? irr::EMIE_RMOUSE_PRESSED_DOWN : irr::EMIE_RMOUSE_LEFT_UP;
        break;
    default:
        return;
    }
    irrEvent.MouseInput.X = event->x();
    irrEvent.MouseInput.Y = event->y();
    irrEvent.MouseInput.Wheel = 0.;
    _device->postEventFromUser(irrEvent);
}

void Q3DZappy::mousePressEvent(QMouseEvent *event)
{
    if (_device != nullptr)
        sendMouseEventToIrrlicht(event, true);
    event->ignore();
}

void Q3DZappy::mouseReleaseEvent(QMouseEvent *event)
{
    if (_device != nullptr)
        sendMouseEventToIrrlicht(event, false);
    event->ignore();
}

void Q3DZappy::wheelEvent(QWheelEvent *event)
{
    if (_device != nullptr && event->orientation() == Qt::Vertical)
    {
        irr::SEvent newEvent;

        newEvent.EventType = irr::EET_MOUSE_INPUT_EVENT;
        newEvent.MouseInput.Event = irr::EMIE_MOUSE_WHEEL;
        newEvent.MouseInput.X = 0;
        newEvent.MouseInput.Y = 0;
        newEvent.MouseInput.Wheel = event->delta() / 120.;
        _device->postEventFromUser(newEvent);
    }
    event->ignore();
}
