#ifndef ZAPPYUI_H
#define ZAPPYUI_H

#include <QWidget>
#include <QString>
#include <QTimer>
#include <map>
#include <QTime>
#include <vector>
#include <list>
#include <QSound>
#include "zappy_communicator.h"
#include "zappystructures.h"
#include "q2dzappy.h"
#include "intro.h"

namespace Ui {
class ZappyUI;
}

class ZappyUI : public QWidget
{
    Q_OBJECT

public:
    explicit ZappyUI(QWidget *parent = 0);
    ~ZappyUI();

private:
    Ui::ZappyUI *ui;
    t_zappy_communicator *communicator;
    QString host;
    unsigned short port;
    QTimer timer;
    QTimer timerZappies;
    std::map<std::string, void (ZappyUI::*)(std::string const &)> updateFunctions;
    QTime now;
    int timeUnit;
    int nbResources;
    std::vector<std::vector<Case *> > cases;
    QString strTeamNames;
    std::map<std::string, Player *> zappies;
    int nbZappiesDed;
    int nbEggs;
    std::map<std::string, Egg *> eggs;
    int refreshTimeout;
    int rowCount;
    QSound *backsound;
    QSound *konichiwa;
    QSound *ded;
    QSound *wololo;
    QSound *cheeki;
    Intro *introWindow;

    void connectToHost();
    void updateZappiesCounter();
    void updateZappieInventaire(Player *zappie);
    void msz(std::string const &);
    void sgt(std::string const &);
    void tna(std::string const &);
    void bct(std::string const &);
    void pnw(std::string const &);
    void ppo(std::string const &);
    void plv(std::string const &);
    void pin(std::string const &);
    void pex(std::string const &);
    void pbc(std::string const &);
    void pic(std::string const &);
    void pie(std::string const &);
    void pfk(std::string const &);
    void pdr(std::string const &);
    void pgt(std::string const &);
    void pdi(std::string const &);
    void enw(std::string const &);
    void eht(std::string const &);
    void ebo(std::string const &);
    void edi(std::string const &);
    void seg(std::string const &);
    void smg(std::string const &);

private slots:
    void updateData();
    void refreshZappies();
};

#endif // ZAPPYUI_H
