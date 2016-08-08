# -*- coding: utf-8 -*-

from zappy_communicator import *
from routine import *


class Communicator:
    def __init__(self):
        self.communicator = createZappyCommunicator()
        if self.communicator is None:
            raise NameError("Communicator creation failed")
        self.isAlive = True
        self.mode = 0
        self.idRadio = 0
        self.id = 0
        self.level = 1
        self.nb_vie = 1260
        self.messages = []

    def connect(self, host, port):
        if connectZappy(self.communicator, host, port) is False:
            raise NameError("Connection to host failed")

    def join_team(self, team):
        resp = ''
        while resp == '':
            resp = self.line()
        if resp != 'BIENVENUE':
            raise NameError("Bad server welcome message : %s" % resp)
        self.send(team)
        resp = ''
        while resp == '':
            resp = self.line()
        if resp == 'ko':
            raise NameError("Can't join team %s" % team)
        map_size = ''
        while map_size == '':
            map_size = self.line()
        return [resp, map_size]

    def disconnect(self):
        disconnectZappy(self.communicator)

    def lastError(self):
        str = returnValueToString(self.communicator)
        if str is None:
            raise NameError("Can't get last error")
        return str

    def send(self, message):
        if message[-1] != '\n':
            message += '\n'
        if sendToHost(self.communicator, message) is False:
            raise NameError("Command sending failed")

    def line(self):
        str_line = getNextLine(self.communicator)
        if str_line is None:
            if statusZappy(self.communicator) is True:
                return ""
            raise NameError("No line to extract and communicator is disconnected")
        if str_line == "mort":
            self.isAlive = False
            self.check_alive()
        if 'niveau actuel : ' in str_line:
            self.level = int(str_line[len("niveau acutel : "):])
        return str_line

    def status(self):
        return statusZappy(self.communicator)

    def check(self):
        ret = ""
        while ret == "":
            ret = self.line()
            if ret == "ko":
                return False
            if ret == "ok":
                return True
            if ret != "":
                self.messages.append(ret)
                ret = ""
        return False

    def check_alive(self):
        if self.isAlive is False:
            raise NameError("I am ded")
        self.isAlive = statusZappy(self.communicator)
        if self.isAlive is False:
            raise NameError("I am ded")

    def avance(self):
        self.check_alive()
        self.send("avance")
        return self.check()

    def droite(self):
        self.check_alive()
        self.send("droite")
        return self.check()

    def gauche(self):
        self.check_alive()
        self.send("gauche")
        return self.check()

    def voir(self):
        self.check_alive()
        self.send("voir")
        vue = ""
        while vue == "":
            vue = self.line()
            if vue != "" and vue[0] != '{':
                self.messages.append(vue)
                vue = ""
        return vue

    def inventaire(self):
        self.check_alive()
        self.send("inventaire")
        treasure = ""
        while treasure == "":
            treasure = self.line()
            if treasure != "" and treasure[0] != '{':
                self.messages.append(treasure)
                treasure = ""
        return treasure

    def prend(self, objet):
        self.check_alive()
        commande = "prend " + str(objet)
        self.send(commande)
        return self.check()

    def pose(self, objet):
        self.check_alive()
        commande = "pose " + str(objet)
        print(commande)
        self.send(commande)
        return self.check()

    def expulse(self):
        self.check_alive()
        self.send("expulse")
        return self.check()

    def broadcast(self, message):
        self.check_alive()
        commande = "broadcast " + message
        self.send(commande)
        return self.check()

    def incantation(self):
        self.check_alive()
        self.send("incantation")
        ret = ""
        while True:
            ret = self.line()
            if ret != "":
                print ret
            if 'niveau actuel : ' in ret:
                try:
                    nb = int(ret[-1])
                    return nb
                except Exception as e:
                    self.messages.append(ret)
                    ret = ""
            elif ret == "ko":
                return False
        return None

    def fork(self):
        self.check_alive()
        self.send("fork")
        return self.check()

    def slots_available(self):
        self.check_alive()
        self.send("connect_nbr")
        ret = ""
        while ret == "":
            ret = self.line()
            if ret != "":
                try:
                    nb = int(ret)
                    return nb
                except Exception as e:
                    self.messages.append(ret)
                    ret = ""
        return None

    def alive(self):
        return self.isAlive

    def postman(self):
        tab = []
        for msg in self.messages:
            tab.append(msg)
        self.messages = []
        while self.alive():
            line = self.line()
            if line != '':
                tab.append(line)
            else:
                return tab

    def search_routine_cmd(self):
        search_routine(self)

    def ascend_routine_cmd(self):
        ascend_routine(self)

    def join_routine_cmd(self):
        join_routine(self)

    def wait_routine_cmd(self):
        wait_routine(self)

    def cosmogonie_cmd(self):
        cosmogonie(self)
