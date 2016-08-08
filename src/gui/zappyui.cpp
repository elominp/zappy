#include <stdexcept>
#include <iostream>
#include <string>
#include <QInputDialog>
#include <QDir>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <cstdio>
#include "zappyui.h"
#include "ui_zappyui.h"

ZappyUI::ZappyUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZappyUI)
{
    ui->setupUi(this);
    this->setWindowTitle("ZappyUI");
    bool ok = false;
    while (!ok || host.isEmpty())
        host = QInputDialog::getText(this, tr("Adresse du serveur"),
                                     tr("Adresse du serveur:"), QLineEdit::Normal,
                                     tr("localhost"), &ok);
    ok = false;
    QString strPort;
    while (!ok || strPort.isEmpty())
        strPort = QInputDialog::getText(this, tr("Port"),
                                        tr("Port de connexion:"), QLineEdit::Normal,
                                        tr(""), &ok);
    port = strPort.toInt();
    communicator = create_zappy_communicator();
    if (communicator == nullptr)
        throw std::runtime_error("Can't create communicator");
    connectToHost();
    now.restart();

    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(updateData()));
    QObject::connect(&timerZappies, SIGNAL(timeout()), this, SLOT(refreshZappies()));

    updateFunctions["msz"] = &ZappyUI::msz;
    updateFunctions["sgt"] = &ZappyUI::sgt;
    updateFunctions["tna"] = &ZappyUI::tna;
    updateFunctions["bct"] = &ZappyUI::bct;
    updateFunctions["pnw"] = &ZappyUI::pnw;
    updateFunctions["ppo"] = &ZappyUI::ppo;
    updateFunctions["plv"] = &ZappyUI::plv;
    updateFunctions["pin"] = &ZappyUI::pin;
    updateFunctions["pex"] = &ZappyUI::pex;
    updateFunctions["pbc"] = &ZappyUI::pbc;
    updateFunctions["pic"] = &ZappyUI::pic;
    updateFunctions["pfk"] = &ZappyUI::pfk;
    updateFunctions["pdr"] = &ZappyUI::pdr;
    updateFunctions["pgt"] = &ZappyUI::pgt;
    updateFunctions["pdi"] = &ZappyUI::pdi;
    updateFunctions["enw"] = &ZappyUI::enw;
    updateFunctions["eht"] = &ZappyUI::eht;
    updateFunctions["ebo"] = &ZappyUI::ebo;
    updateFunctions["seg"] = &ZappyUI::seg;
    updateFunctions["smg"] = &ZappyUI::smg;
    nbResources = 0;
    nbZappiesDed = 0;
    nbEggs = 0;
    refreshTimeout = 1;
    timeUnit = 0;
    ui->tableau->setEditTriggers(QAbstractItemView::NoEditTriggers);
    rowCount = 0;
    ui->sfmlView->setGroundTileset("ground.png");
    ui->sfmlView->setItemsTileset("resources.png");
    std::vector<std::string> tileset;
    tileset.push_back("zappie1.png");
    tileset.push_back("zappie2.png");
    tileset.push_back("zappie3.png");
    tileset.push_back("zappie4.png");
    tileset.push_back("zappie5.png");
    tileset.push_back("zappie6.png");
    tileset.push_back("zappie7.png");
    tileset.push_back("zappie8.png");
    ui->sfmlView->setZappieTileset(tileset);
    ui->sfmlView->setZappyZappies(zappies);
    ui->sfmlView->setZappyEggs(eggs);
    ui->sfmlView->setEggTileset("egg.png");
    ui->sfmlView->setBroadcastTileset("broadcast.png");
    timer.start(refreshTimeout);
    backsound = new QSound("backsound.wav");
    backsound->play();
    backsound->setLoops(2147483647);
    konichiwa = new QSound("konichiwa.wav");
    ded = new QSound("ded.wav");
    wololo = new QSound("wololo.wav");
    cheeki = new QSound("cheeki.wav");
    introWindow = nullptr;
}

void ZappyUI::connectToHost()
{
    char *buffer;

    if (communicator->connect(communicator, host.toStdString().c_str(), port) == nullptr)
    {
        std::cerr << "Can't connect to host because of " << communicator->return_value_to_string(communicator) << std::endl;
        throw std::runtime_error("Can't connect to host");
    }
    fflush(stderr);
    while ((buffer = communicator->getnextline(communicator)) == nullptr)
        usleep(0);
    std::string str(buffer);
    if (str != "BIENVENUE")
    {
        std::cerr << "Host didn't send good welcome message, i am connected to the good server ?" << std::endl;
        throw std::runtime_error("Bad welcome message");
    }
    communicator->send(communicator, "GRAPHIC\n");
}

void ZappyUI::updateData()
{
    char *buffer;

    while ((buffer = communicator->getnextline(communicator)) != nullptr)
    {
        char *args = buffer;
        while (*args != '\0')
        {
            if (*args == ' ')
            {
                *args = '\0';
                args++;
                break;
            }
            args++;
        }
        std::string cmd(buffer);
        std::string sarg(args);
        try
        {
            void (ZappyUI::*fct)(std::string const &) = updateFunctions.at(cmd);
            (this->*fct)(sarg);
        }
        catch (std::out_of_range)
        {

        }
        delete buffer;
    }
    if (communicator->communicator == nullptr || !communicator->communicator->status)
        exit(0);
    ui->nb_cycles_saw->display((now.elapsed() / 1000) * timeUnit);
    timer.start(refreshTimeout);
}

void ZappyUI::msz(std::string const &args)
{
    QString data;
    data = args.c_str();
    QStringList xy = data.split(' ');
    if (xy.length() < 2)
        return;
    //introWindow = new Intro;
    //introWindow->show();
    //this->hide();
    //backsound->stop();
    QString x = xy.at(0);
    QString y = xy.at(1);
    int iy = y.toInt();
    int ix = x.toInt();
    ui->length_map->display(ix);
    ui->height_map->display(iy);
    cases.resize(iy + 1);
    for (std::size_t i = 0; i < iy; i++)
    {
        std::vector<Case *> &row = cases[i];
        row.resize(ix + 1);
    }
    ui->sfmlView->setZappyMap(cases);
    ui->sfmlView->setMapSize(ix, iy);
}

void ZappyUI::sgt(const std::string &args)
{
    timeUnit = atoi(args.c_str());
    timerZappies.start(1000);
}

void ZappyUI::tna(const std::string &args)
{
    /* if (introWindow != nullptr)
    {
        introWindow->stop();
        delete introWindow;
        introWindow = nullptr;
        //this->show();
        backsound->play();
    } */
    if (ui->teamNames->text() == "")
        strTeamNames = args.c_str();
    else
    {
        strTeamNames += " - ";
        strTeamNames += args.c_str();
    }
    ui->teamNames->setText(strTeamNames);
}

void ZappyUI::bct(std::string const &args)
{
    QString data;
    data = args.c_str();
    QStringList list = data.split(' ');
    if (list.length() < 9)
        return;
    QString x = list.at(0);
    QString y = list.at(1);
    QString feed = list.at(2);
    QString linemate = list.at(3);
    QString deraumere = list.at(4);
    QString sibur = list.at(5);
    QString mendiane = list.at(6);
    QString phiras = list.at(7);
    QString thystame = list.at(8);
    int iy = y.toInt();
    if (iy >= cases.size())
        return;
    std::vector<Case *> &row = cases[iy];
    Case *tile;
    int ix = x.toInt();
    if (ix >= row.size())
        return;
    if (row[ix] == nullptr)
        tile = new Case;
    else
    {
        tile = row[ix];
        nbResources -= tile->feed;
        nbResources -= tile->linemate;
        nbResources -= tile->deraumere;
        nbResources -= tile->sibur;
        nbResources -= tile->mendiane;
        nbResources -= tile->phiras;
        nbResources -= tile->thystame;
    }
    tile->feed = feed.toInt();
    tile->linemate = linemate.toInt();
    tile->deraumere = deraumere.toInt();
    tile->sibur = sibur.toInt();
    tile->mendiane = mendiane.toInt();
    tile->phiras = phiras.toInt();
    tile->thystame = thystame.toInt();
    row[ix] = tile;
    nbResources += tile->feed;
    nbResources += tile->linemate;
    nbResources += tile->deraumere;
    nbResources += tile->sibur;
    nbResources += tile->mendiane;
    nbResources += tile->phiras;
    nbResources += tile->thystame;
    ui->nb_resources->display(nbResources);
}

void ZappyUI::pnw(const std::string &args)
{
    QString data;
    data = args.c_str();
    QStringList list = data.split(' ');
    if (list.length() < 6)
        return;
    QString playerId = list.at(0);
    QString x = list.at(1);
    QString y = list.at(2);
    QString orientation = list.at(3);
    QString lvl = list.at(4);
    QString team = list.at(5);
    Player *zappie = zappies[playerId.toStdString()];
    if (zappie == nullptr)
        zappie = new Player;
    zappie->orientation = orientation.toInt();
    zappie->lvl = lvl.toInt();
    zappie->teamName = team.toStdString();
    zappie->x = x.toInt();
    zappie->y = y.toInt();
    zappie->id = playerId.toStdString();
    zappie->deraumere = 0;
    zappie->eggs = 0;
    zappie->feed = 0;
    zappie->linemate = 0;
    zappie->mendiane = 0;
    zappie->phiras = 0;
    zappie->sibur = 0;
    zappie->thystame = 0;
    zappie->broadcast = false;
    zappie->incante = false;
    zappie->rowIdx = rowCount;
    rowCount++;
    zappies[playerId.toStdString()] = zappie;
    updateZappiesCounter();
    ui->tableau->setRowCount(rowCount);
    ui->tableau->setItem(zappie->rowIdx, 0, new QTableWidgetItem(QString(zappie->id.c_str())));
    ui->tableau->setItem(zappie->rowIdx, 1, new QTableWidgetItem(x + QString(" ; ") + y));
    ui->tableau->setItem(zappie->rowIdx, 2, new QTableWidgetItem(lvl));
    ui->tableau->setItem(zappie->rowIdx, 3, new QTableWidgetItem("Vivant"));
    ui->tableau->setItem(zappie->rowIdx, 4, new QTableWidgetItem("0"));
    ui->tableau->setItem(zappie->rowIdx, 5, new QTableWidgetItem("0"));
    ui->tableau->setItem(zappie->rowIdx, 6, new QTableWidgetItem("0"));
    ui->tableau->setItem(zappie->rowIdx, 7, new QTableWidgetItem("0"));
    ui->tableau->setItem(zappie->rowIdx, 8, new QTableWidgetItem("0"));
    ui->tableau->setItem(zappie->rowIdx, 9, new QTableWidgetItem("0"));
    ui->tableau->setItem(zappie->rowIdx, 10, new QTableWidgetItem("0"));
    ui->tableau->setItem(zappie->rowIdx, 11, new QTableWidgetItem("0"));
    konichiwa->play();
}

void ZappyUI::updateZappiesCounter()
{
    int nbZappies = zappies.size();
    ui->nb_zappies->display(nbZappies);
    ui->nb_alive->display(nbZappies - nbZappiesDed);
    ui->nb_ded->display(nbZappiesDed);
    ui->nb_eggs->display(nbEggs);
}

void ZappyUI::ppo(const std::string &args)
{
    QString data;
    data = args.c_str();
    QStringList list = data.split(' ');
    if (list.length() < 4)
        return;
    QString playerId = list.at(0);
    QString strX = list.at(1);
    QString strY = list.at(2);
    QString orientation = list.at(3);
    Player *zappie;
    try
    {
        zappie = zappies.at(playerId.toStdString());
    }
    catch (std::out_of_range)
    {
        return;
    }
    if (zappie == nullptr)
        return;
    zappie->x = strX.toInt();
    zappie->y = strY.toInt();
    zappie->orientation = orientation.toInt();
    zappie->broadcast = false;
    zappie->incante = false;
    QTableWidgetItem *item = new QTableWidgetItem();
    /* if (item = nullptr)
        item = new QTableWidgetItem(); */
    item->setText(strX + QString(" ; ") + strY);
    ui->tableau->setItem(zappie->rowIdx, 1, item);
}

void ZappyUI::plv(const std::string &args)
{
    QString data;
    data = args.c_str();
    QStringList list = data.split(' ');
    if (list.length() < 2)
        return;
    QString playerId = list.at(0);
    QString strLvl = list.at(1);
    Player *zappie;
    try
    {
        zappie = zappies.at(playerId.toStdString());
    }
    catch (std::out_of_range)
    {
        return;
    }
    if (zappie == nullptr)
        return;
    zappie->lvl = strLvl.toInt();
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setText(strLvl);
    ui->tableau->setItem(zappie->rowIdx, 2, item);
}

void ZappyUI::pin(const std::string &args)
{
    QString data;
    data = args.c_str();
    QStringList list = data.split(' ');
    if (list.length() < 10)
        return;
    QString playerId = list.at(0);
    QString strX = list.at(1);
    QString strY = list.at(2);
    QString strFeed = list.at(3);
    QString strLinemate = list.at(4);
    QString strDeraumere = list.at(5);
    QString strSibur = list.at(6);
    QString strMendiane = list.at(7);
    QString strPhiras = list.at(8);
    QString strThystame = list.at(9);
    Player *zappie;
    try
    {
        zappie = zappies.at(playerId.toStdString());
    }
    catch (std::out_of_range)
    {
        return;
    }
    if (zappie == nullptr)
        return;
    zappie->x = strX.toInt();
    zappie->y = strY.toInt();
    zappie->feed = strFeed.toInt();
    zappie->linemate = strLinemate.toInt();
    zappie->deraumere = strDeraumere.toInt();
    zappie->sibur = strSibur.toInt();
    zappie->mendiane = strMendiane.toInt();
    zappie->phiras = strPhiras.toInt();
    zappie->thystame = strThystame.toInt();
    QTableWidgetItem *feed = new QTableWidgetItem();
    QTableWidgetItem *linemate = new QTableWidgetItem();
    QTableWidgetItem *deraumere = new QTableWidgetItem();
    QTableWidgetItem *sibur = new QTableWidgetItem();
    QTableWidgetItem *mendiane = new QTableWidgetItem();
    QTableWidgetItem *phiras = new QTableWidgetItem();
    QTableWidgetItem *thystame = new QTableWidgetItem();
    feed->setText(strFeed);
    linemate->setText(strLinemate);
    deraumere->setText(strDeraumere);
    sibur->setText(strSibur);
    mendiane->setText(strMendiane);
    phiras->setText(strPhiras);
    thystame->setText(strThystame);
    ui->tableau->setItem(zappie->rowIdx, 5, feed);
    ui->tableau->setItem(zappie->rowIdx, 6, linemate);
    ui->tableau->setItem(zappie->rowIdx, 7, deraumere);
    ui->tableau->setItem(zappie->rowIdx, 8, sibur);
    ui->tableau->setItem(zappie->rowIdx, 9, mendiane);
    ui->tableau->setItem(zappie->rowIdx, 10, phiras);
    ui->tableau->setItem(zappie->rowIdx, 11, thystame);
}

void ZappyUI::pex(const std::string &args)
{
    QString data;
    data = args.c_str();
    QStringList list = data.split(' ');
    if (list.length() < 1)
        return;
    QString playerId = list.at(0);
    Player *zappie;
    try
    {
        zappie = zappies.at(playerId.toStdString());
    }
    catch (std::out_of_range)
    {
        return;
    }
    if (zappie == nullptr)
        return;
    zappie->broadcast = false;
    zappie->incante = false;
}

void ZappyUI::pbc(const std::string &args)
{
    QString data;
    data = args.c_str();
    QStringList list = data.split(' ');
    if (list.length() < 2)
        return;
    QString strId = list.at(0);
    Player *zappie;
    try
    {
        zappie = zappies.at(strId.toStdString());
    }
    catch (std::out_of_range)
    {
        return;
    }
    if (zappie == nullptr)
        return;
    zappie->broadcast = true;
    zappie->incante = false;
    ui->zappiesBroadcast->append(QString(args.c_str()));
}

void ZappyUI::pic(const std::string &args)
{
    QString data;
    data = args.c_str();
    QStringList list = data.split(' ');
    if (list.length() < 4)
        return;
    QString strX = list.at(0);
    QString strY = list.at(1);
    QString strIncantionLvl = list.at(2);
    QString strIncanteur = list.at(3);
    Player *zappie;
    try
    {
        zappie = zappies.at(strIncanteur.toStdString());
    }
    catch (std::out_of_range)
    {
        return;
    }
    zappie->broadcast = false;
    zappie->incante = true;
}

void ZappyUI::pie(const std::string &args)
{
    QString data;
    data = args.c_str();
    QStringList list = data.split(' ');
    if (list.length() < 3)
        return;
    QString strX = list.at(0);
    QString strY = list.at(1);
    QString strResult = list.at(2);
    int result = strResult.toInt();
    if (result)
    {
        cheeki->play();
    }
    else
    {
        wololo->play();
    }
}

void ZappyUI::pfk(const std::string &args)
{
    QString data;
    data = args.c_str();
    QStringList list = data.split(' ');
    if (list.length() < 1)
        return;
    QString playerId = list.at(0);
    Player *zappie;
    try
    {
        zappie = zappies.at(playerId.toStdString());
    }
    catch (std::out_of_range)
    {
        return;
    }
    if (zappie == nullptr)
        return;
    zappie->broadcast = false;
    zappie->incante = false;
}

void ZappyUI::pdr(const std::string &args)
{
    QString data;
    data = args.c_str();
    QStringList list = data.split(' ');
    if (list.length() < 2)
        return;
    QString playerId = list.at(0);
    QString strResourceId = list.at(1);
    int resourceId = strResourceId.toInt();
    Player *zappie;
    try
    {
        zappie = zappies.at(playerId.toStdString());
    }
    catch (std::out_of_range)
    {
        return;
    }
    if (zappie == nullptr)
        return;
    int *resource;

    if (resourceId == 0)
        resource = &zappie->feed;
    else if (resourceId == 1)
        resource = &zappie->linemate;
    else if (resourceId == 2)
        resource = &zappie->deraumere;
    else if (resourceId == 3)
        resource = &zappie->sibur;
    else if (resourceId == 4)
        resource = &zappie->mendiane;
    else if (resourceId == 5)
        resource = &zappie->phiras;
    else if (resourceId == 6)
        resource = &zappie->thystame;
    else
        resource = nullptr;
    if (resource != nullptr)
    {
        nbResources++;
        *resource -= 1;
        updateZappiesCounter();
        updateZappieInventaire(zappie);
    }
    zappie->broadcast = false;
    zappie->incante = false;
}

void ZappyUI::updateZappieInventaire(Player *zappie)
{
    if (zappie == nullptr)
        return;
    std::string strFeed = std::to_string(zappie->feed);
    std::string strLinemate = std::to_string(zappie->linemate);
    std::string strDeraumere = std::to_string(zappie->deraumere);
    std::string strSibur = std::to_string(zappie->sibur);
    std::string strMendiane = std::to_string(zappie->mendiane);
    std::string strPhiras = std::to_string(zappie->phiras);
    std::string strThystame = std::to_string(zappie->thystame);
    QTableWidgetItem *feed = new QTableWidgetItem();
    QTableWidgetItem *linemate = new QTableWidgetItem();
    QTableWidgetItem *deraumere = new QTableWidgetItem();
    QTableWidgetItem *sibur = new QTableWidgetItem();
    QTableWidgetItem *mendiane = new QTableWidgetItem();
    QTableWidgetItem *phiras = new QTableWidgetItem();
    QTableWidgetItem *thystame = new QTableWidgetItem();
    feed->setText(QString(strFeed.c_str()));
    linemate->setText(QString(strLinemate.c_str()));
    deraumere->setText(QString(strDeraumere.c_str()));
    sibur->setText(QString(strSibur.c_str()));
    mendiane->setText(QString(strMendiane.c_str()));
    phiras->setText(QString(strPhiras.c_str()));
    thystame->setText(QString(strThystame.c_str()));
    ui->tableau->setItem(zappie->rowIdx, 5, feed);
    ui->tableau->setItem(zappie->rowIdx, 6, linemate);
    ui->tableau->setItem(zappie->rowIdx, 7, deraumere);
    ui->tableau->setItem(zappie->rowIdx, 8, sibur);
    ui->tableau->setItem(zappie->rowIdx, 9, mendiane);
    ui->tableau->setItem(zappie->rowIdx, 10, phiras);
    ui->tableau->setItem(zappie->rowIdx, 11, thystame);
}

void ZappyUI::pgt(const std::string &args)
{
    QString data;
    data = args.c_str();
    QStringList list = data.split(' ');
    if (list.length() < 2)
        return;
    QString playerId = list.at(0);
    QString strResourceId = list.at(1);
    int resourceId = strResourceId.toInt();
    Player *zappie;
    try
    {
        zappie = zappies.at(playerId.toStdString());
    }
    catch (std::out_of_range)
    {
        return;
    }
    if (zappie == nullptr)
        return;
    int *resource;

    if (resourceId == 0)
        resource = &zappie->feed;
    else if (resourceId == 1)
        resource = &zappie->linemate;
    else if (resourceId == 2)
        resource = &zappie->deraumere;
    else if (resourceId == 3)
        resource = &zappie->sibur;
    else if (resourceId == 4)
        resource = &zappie->mendiane;
    else if (resourceId == 5)
        resource = &zappie->phiras;
    else if (resourceId == 6)
        resource = &zappie->thystame;
    else
        resource = nullptr;
    if (resource != nullptr)
    {
        nbResources--;
        *resource += 1;
        updateZappiesCounter();
        updateZappieInventaire(zappie);
    }
    zappie->broadcast = false;
    zappie->incante = false;
}

void ZappyUI::pdi(const std::string &args)
{
    QString data;
    data = args.c_str();
    QStringList list = data.split(' ');
    if (list.length() < 1)
        return;
    Player *zappie;
    QString playerId = list.at(0);
    try
    {
        zappie = zappies.at(playerId.toStdString());
    }
    catch (std::out_of_range)
    {
        return;
    }
    if (zappie == nullptr)
        return;
    QTableWidgetItem *status = new QTableWidgetItem();
    /* if (status == nullptr)
        status = new QTableWidgetItem(); */
    status->setText("Ded");
    ui->tableau->setItem(zappie->rowIdx, 3, status);
    delete zappie;
    zappies[playerId.toStdString()] = nullptr;
    nbZappiesDed++;
    updateZappiesCounter();
    ded->play();
}

void ZappyUI::enw(const std::string &args)
{
    QString data;
    data = args.c_str();
    QStringList list = data.split(' ');
    if (list.length() < 4)
        return;
    QString eggId = list.at(0);
    QString playerId = list.at(1);
    QString strX = list.at(2);
    QString strY = list.at(3);
    Egg *egg = new Egg;
    Player *player;
    try
    {
        player = zappies.at(playerId.toStdString());
        if (player == nullptr)
            return;
    }
    catch (std::out_of_range)
    {
        return;
    }
    egg->id = eggId.toStdString();
    egg->x = strX.toInt();
    egg->y = strY.toInt();
    player->eggs += 1;
    nbEggs += 1;
    eggs[eggId.toStdString()] = egg;
    updateZappiesCounter();
    player->broadcast = false;
    player->incante = false;
    QTableWidgetItem *eg = new QTableWidgetItem();
    /* if (eg == nullptr)
        eg = new QTableWidgetItem(); */
    std::string strNbEggs = std::to_string(player->eggs);
    eg->setText(QString(strNbEggs.c_str()));
    ui->tableau->setItem(player->rowIdx, 5, eg);
}

void ZappyUI::eht(const std::string &args)
{
    QString data;
    data = args.c_str();
    QStringList list = data.split(' ');
    if (list.length() < 1)
        return;
    QString eggId = list.at(0);
    Egg *egg;
    try
    {
        egg = eggs.at(eggId.toStdString());
        if (egg == nullptr)
            return;
    }
    catch (std::out_of_range)
    {
        return;
    }
    delete egg;
    nbEggs--;
    eggs[eggId.toStdString()] = nullptr;
    updateZappiesCounter();
}

void ZappyUI::ebo(const std::string &args)
{
    QString data;
    data = args.c_str();
    QStringList list = data.split(' ');
    if (list.length() < 1)
        return;
    QString eggId = list.at(0);
    Egg *egg;
    try
    {
        egg = eggs.at(eggId.toStdString());
        if (egg == nullptr)
            return;
    }
    catch (std::out_of_range)
    {
        return;
    }
}

void ZappyUI::edi(const std::string &args)
{
    QString data;
    data = args.c_str();
    QStringList list = data.split(' ');
    if (list.length() < 1)
        return;
    QString eggId = list.at(0);
    Egg *egg;
    try
    {
        egg = eggs.at(eggId.toStdString());
        if (egg == nullptr)
            return;
    }
    catch (std::out_of_range)
    {
        return;
    }
    delete egg;
    nbEggs--;
    eggs[eggId.toStdString()] = nullptr;
    updateZappiesCounter();
}

void ZappyUI::seg(const std::string &args)
{
    QMessageBox::information(this, "Fin de serveur",
                             QString("L'équipe ") + QString(args.c_str()) + " a gagnée.");
    exit(0);
}

void ZappyUI::smg(const std::string &args)
{
    QMessageBox::information(this, "Message du serveur",
                             QString("Le serveur indique ceci : ") + QString(args.c_str()));
}

void ZappyUI::refreshZappies()
{
    for (auto it = zappies.begin(); it != zappies.end(); it++)
    {
        Player *zappie = it->second;

        if (zappie != nullptr)
        {
            communicator->send(communicator, "plv %s\n", zappie->id.c_str());
            communicator->send(communicator, "pin %s\n", zappie->id.c_str());
        }
    }
    timerZappies.start(1000);
}

ZappyUI::~ZappyUI()
{
    delete ui;
}
