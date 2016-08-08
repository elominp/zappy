#ifndef ZAPPYSTRUCTURES_H
#define ZAPPYSTRUCTURES_H

#include <string>

typedef struct Egg
{
    std::string id;
    int x;
    int y;
} Egg;

typedef struct Player
{
    int orientation;
    int lvl;
    int x;
    int y;
    std::string teamName;
    std::string id;
    int feed;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
    int eggs;
    bool broadcast;
    bool incante;
    int rowIdx;
} Player;

typedef struct Case
{
    int feed;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} Case;

#endif // ZAPPYSTRUCTURES_H
