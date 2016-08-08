#ifndef Q2DZAPPY_H
#define Q2DZAPPY_H

#include <QWidget>
#include <QTimer>
#include <QShowEvent>
#include <QPaintEvent>
#include <QMouseEvent>
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "zappystructures.h"

class Q2DZappy : public QWidget, public sf::RenderWindow
{
    Q_OBJECT
public:
    explicit Q2DZappy(QWidget *parent = 0);
    QPaintEngine *paintEngine() const;
    void setGroundTileset(std::string const &);
    void setItemsTileset(std::string const &);
    void setZappieTileset(std::vector<std::string> const &);
    void setEggTileset(std::string const &);
    void setBroadcastTileset(std::string const &);
    void setZappyMap(std::vector<std::vector<Case *> > const &);
    void setZappyZappies(std::map<std::string, Player *> const &);
    void setZappyEggs(std::map<std::string, Egg *> const &);
    void setMapSize(int, int);

signals:

public slots:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    QTimer _timer;
    const std::vector<std::vector<Case *> > *_map;
    const std::map<std::string, Player *> *_zappies;
    const std::map<std::string, Egg *> *_eggs;
    sf::View _view;
    sf::Texture _groundTileset;
    sf::Texture _itemsTileset;
    std::vector<sf::Texture> _zappieTileset;
    sf::Texture _eggTileset;
    sf::Texture _broadcastTileset;
    int _width;
    int _height;

    void _init();
    void _update();
    void _updateMap();
    void _updateResources();
    void _updateZappies();
    void _updateEggs();
};

#endif // Q2DZAPPY_H
