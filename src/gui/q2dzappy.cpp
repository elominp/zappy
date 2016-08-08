#include <iostream>
#include "q2dzappy.h"

Q2DZappy::Q2DZappy(QWidget *parent) :
    QWidget(parent),
    sf::RenderWindow((sf::WindowHandle)this->winId())
{
    this->setAttribute(Qt::WA_PaintOnScreen);
    this->setAttribute(Qt::WA_OpaquePaintEvent);
    this->setAttribute(Qt::WA_NoSystemBackground);
    sf::Vector2u realSize;
    QSize widgetSize = this->size();
    realSize.x = widgetSize.width();
    realSize.y = widgetSize.height();
    this->setSize(realSize);
    _init();
    QObject::connect(&_timer, SIGNAL(timeout()), this, SLOT(repaint()));
    _timer.start(16);
}

QPaintEngine *Q2DZappy::paintEngine() const
{
    return nullptr;
}

void Q2DZappy::paintEvent(QPaintEvent *event)
{
    _update();
    this->display();
    event->accept();
}

void Q2DZappy::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    sf::Vector2u realSize;

    QSize widgetSize = this->size();
    realSize.x = widgetSize.width();
    realSize.y = widgetSize.height();
    this->setSize(realSize);

    _view = sf::View(sf::FloatRect(0., 0.,
                                   static_cast<float>(realSize.x),
                                   static_cast<float>(realSize.y)));
    this->setView(_view);
}

void Q2DZappy::_init()
{
    sf::RenderWindow::clear(sf::Color(0, 0, 0));
    _width = 0;
    _height = 0;
    _map = nullptr;
    _zappies = nullptr;
    _eggs = nullptr;
}

void Q2DZappy::_update()
{
    sf::RenderWindow::clear(sf::Color(0, 0, 0));
    _updateMap();
    _updateResources();
    _updateZappies();
    _timer.start(16);
}

void Q2DZappy::setGroundTileset(std::string const &path)
{
    if (_groundTileset.loadFromFile(path) == false)
        throw std::runtime_error(std::string("Unable to load sprite " + path));
}

void Q2DZappy::setItemsTileset(std::string const &path)
{
    if (_itemsTileset.loadFromFile(path) == false)
        throw (std::runtime_error(std::string("can't load texture file " + path)));
}

void Q2DZappy::setZappieTileset(std::vector<std::string> const &paths)
{
    int i = 0;
    _zappieTileset.clear();
    _zappieTileset.resize(paths.size());
    for (auto it = paths.begin(); it != paths.end(); it++)
    {
        sf::Texture &texture = _zappieTileset[i];
        if (texture.loadFromFile(*it) == false)
            throw std::runtime_error(std::string("Can't load texture file " + *it));
        i++;
    }
}

void Q2DZappy::setZappyMap(std::vector<std::vector<Case *> > const &map)
{
    _map = &map;
}

void Q2DZappy::setZappyZappies(std::map<std::string, Player *> const &zappies)
{
    _zappies = &zappies;
}

void Q2DZappy::setZappyEggs(std::map<std::string, Egg *> const &eggs)
{
    _eggs = &eggs;
}

void Q2DZappy::setMapSize(int width, int height)
{
    _width = width;
    _height = height;
}

void Q2DZappy::_updateMap()
{
    sf::IntRect tile;

    tile.left = 256;
    tile.top = 320;
    tile.width = 64;
    tile.height = 64;
    if (_map != nullptr)
    {
        for (int y = 0; y < _height; y++)
        {
            for (int x = 0; x < _width; x++)
            {
                sf::Sprite sprite(_groundTileset, tile);
                sprite.move((x * 32) - (y * 32), (y * 16) + (x * 16));
                this->draw(sprite);
            }
        }
    }
}

void Q2DZappy::_updateResources()
{
    sf::IntRect tile;

    tile.top = 0;
    tile.width = 16;
    tile.height = 16;
    if (_map != nullptr)
    {
        for (int y = 0; y < _height; y++)
        {
            std::vector<Case *> const &row = _map->at(y);
            for (int x = 0; x < _width; x++)
            {
                Case *bloc = row.at(x);
                if (bloc->feed)
                {
                    tile.left = 0;
                    sf::Sprite sprite(_itemsTileset, tile);
                    sprite.move((x * 32) - (y * 32), (y * 16) + (x * 16) + 8);
                    this->draw(sprite);
                }
                if (bloc->linemate)
                {
                    tile.left = 16;
                    sf::Sprite sprite(_itemsTileset, tile);
                    sprite.move((x * 32) - (y * 32) + 16, (y * 16) + (x * 16) + 8);
                    this->draw(sprite);
                }
                if (bloc->deraumere)
                {
                    tile.left = 32;
                    sf::Sprite sprite(_itemsTileset, tile);
                    sprite.move((x * 32) - (y * 32) + 32, (y * 16) + (x * 16) + 8);
                    this->draw(sprite);
                }
                if (bloc->sibur)
                {
                    tile.left = 48;
                    sf::Sprite sprite(_itemsTileset, tile);
                    sprite.move((x * 32) - (y * 32) + 48, (y * 16) + (x * 16) + 8);
                    this->draw(sprite);
                }
                if (bloc->mendiane)
                {
                    tile.left = 64;
                    sf::Sprite sprite(_itemsTileset, tile);
                    sprite.move((x * 32) - (y * 32) + 32, (y * 16) + (x * 16));
                    this->draw(sprite);
                }
                if (bloc->phiras)
                {
                    tile.left = 80;
                    sf::Sprite sprite(_itemsTileset, tile);
                    sprite.move((x * 32) - (y * 32) + 32, (y * 16) + (x * 16) + 16);
                    this->draw(sprite);
                }
                if (bloc->thystame)
                {
                    tile.left = 96;
                    sf::Sprite sprite(_itemsTileset, tile);
                    sprite.move((x * 32) - (y * 32) + 16, (y * 16) + (x * 16) + 16);
                    this->draw(sprite);
                }
            }
        }
    }
}

void Q2DZappy::_updateZappies()
{
    if (_zappies != nullptr)
    {
        sf::IntRect tile;

        tile.left = 0;
        tile.width = 32;
        tile.height = 64;
        for (std::map<std::string, Player *>::const_iterator it = _zappies->begin(); it != _zappies->end(); it++)
        {
            Player *zappie = it->second;
            if (zappie != nullptr)
            {
                switch (zappie->orientation)
                {
                case 1:
                    tile.top = 166;
                    break;
                case 2:
                    tile.top = 2;
                    break;
                case 3:
                    tile.top = 76;
                    break;
                case 4:
                    tile.top = 254;
                    break;
                default:
                    tile.top = 0;
                }
                sf::Sprite sprite(_zappieTileset[zappie->lvl - 1], tile);
                sprite.move((zappie->x * 32) - (zappie->y * 32), (zappie->y * 16) + (zappie->x * 16) - 32);
                this->draw(sprite);

                if (zappie->broadcast)
                {
                    sf::Sprite broad(_broadcastTileset);
                    broad.move((zappie->x * 32) - (zappie->y * 32) - 8, (zappie->y * 16) + (zappie->x * 16) - 80);
                    this->draw(broad);
                }
            }
        }
    }
}

void Q2DZappy::mousePressEvent(QMouseEvent *event)
{
    if (event->y() >= (this->height() / 2) &&
        (event->x() >= (this->width() / 4) && event->x() < ((this->width() / 4) * 3)))
        _view.move(0., this->height() / 10.);
    else if (event->y() < (this->height() / 2) &&
             (event->x() >= (this->width() / 4) && event->x() < ((this->width() / 4) * 3)))
        _view.move(0., -(this->height() / 10.));
    else if (event->x() < (this->width() / 4))
        _view.move(-(this->width() / 10.), 0.);
    else
        _view.move(this->width() / 10., 0.);
    this->setView(_view);
    event->accept();
}

void Q2DZappy::setEggTileset(std::string const &path)
{
    if (_eggTileset.loadFromFile(path) == false)
        throw std::runtime_error("Unable to load texture " + path);
}

void Q2DZappy::setBroadcastTileset(std::string const &path)
{
    if (_broadcastTileset.loadFromFile(path) == false)
        throw std::runtime_error("Unable to load texture " + path);
}

void Q2DZappy::_updateEggs()
{
    if (_eggs != nullptr)
    {
        for (auto it = _eggs->begin(); it != _eggs->end(); it++)
        {
            Egg *egg = it->second;
            if (egg == nullptr)
                continue;
            sf::Sprite sprite(_eggTileset);
            sprite.move((egg->x * 32) - (egg->y * 32), (egg->y * 16) + (egg->x * 16));
            this->draw(sprite);
        }
    }
}
