#!/usr/bin/python
import misc
from copy import deepcopy
import voir_cmd
import inventaire_cmd
import process_action_list


def get_ores_nb_in_case(case, ore):
    result = 0
    for i in range(0, len(case["ores"])):
        if case["ores"][i] == ore:
            result += 1
    return result


def get_ores_in_inventory(inventory, ore):
    result = 0
    for i in range(0, len(inventory)):
        if inventory[i]["type"] == ore:
            result = int(inventory[i]["nb"])
    return result


def check_elevation(level, inventory, case):
    current_tab = deepcopy(misc.lvl_ore_priority_tab[level - 1])
    for i in range(0, len(current_tab)):
        current_check = int(current_tab[0][i]["nb"])
        current_check -= get_ores_in_inventory(inventory, current_tab[0][i]["type"])
        current_check -= get_ores_nb_in_case(case, current_tab[0][i]["type"])
        if current_check > 0:
            return False
    return True


def check_case(level, case):
    current_tab = deepcopy(misc.lvl_ore_priority_tab[level - 1])
    for i in range(0, len(current_tab)):
        current_check = int(current_tab[0][i]["nb"])
        current_check -= get_ores_nb_in_case(case, current_tab[0][i]["type"])
        if current_check > 0:
            return False
    return True


def check_nb_players(level, case):
    if misc.nb_players_on_case[level - 1] > case["players"]:
        return False
    return True


def drop_on_case(com, level, case, nb_players):
    current_tab = deepcopy(misc.lvl_ore_priority_tab[level - 1])
    for i in range(0, len(current_tab[0])):
        current_check = int(current_tab[0][i]["nb"]) - get_ores_nb_in_case(case, current_tab[0][i]["type"])
        print("%s : " % current_tab[0][i]["type"], "j'ai besoin de %d pierres et j'en ai actuellement" % current_tab[0][i]["nb"], " %d" % get_ores_nb_in_case(case, current_tab[0][i]["type"]))
        while current_check > 0:
            for k in range(0, len(misc.ressource_tab)):
                if misc.ressource_tab[k][1] == current_tab[0][i]["type"]:
                    ret = com.pose(misc.ressource_tab[k][0])
                    if ret:
                        case["ores"].append(misc.ressource_tab[k][1])
                        print("j'ai pose ", misc.ressource_tab[k][0])
                    else:
                        print(com.inventaire())
                        print("je n'ai pas reussi a poser :", misc.ressource_tab[k][0])
                    if level != 1 and nb_players > 0:
                        com.broadcast("elevation level:" + str(level) + ";id:" + str(com.id))
            current_check -= 1
    return case


def check_players_arrived(messages, nb_players, id):
    i = 0
    while len(messages) > 0:
        if "message 0,joined " + str(id) == messages[i]:
            nb_players -= 1
        elif messages[i] == "message 0,aborted " + str(id):
            nb_players += 1
        del messages[i]
    return nb_players


def take_the_too(com, case):
    current_tab = deepcopy(misc.lvl_ore_priority_tab[com.level - 1])
    for i in range(0, len(current_tab[0])):
        current_check = get_ores_nb_in_case(case, current_tab[0][i]["type"]) - int(current_tab[0][i]["nb"])
        while current_check > 0:
            pos = int(current_tab[0][i]["type"]) - 1
            print(misc.ressource_tab[pos][0])
            com.prend(misc.ressource_tab[pos][0])
            if com.level != 1:
                com.broadcast("elevation level:" + str(com.level) + ";id:" + str(com.id))
            current_check -= 1


def elevation(com, level, inventory, case):
    nb_players = misc.nb_players_on_case[level - 1] - 1
    food = inventaire_cmd.get_food_quantity(inventory)
    if check_elevation(level, inventory, case):
        if nb_players > 0:
            print("In waiting players boucle")
        if process_action_list.check_join(com.postman(), com) and food > misc.enough_food:
            com.mode = 2
            return
        while nb_players > 0 and food > misc.critical_food:
            com.broadcast("elevation level:" + str(level) + ";id:" + str(com.id))
            if check_case(level, case) == False:
                case = drop_on_case(com, level, case, nb_players)
            if level != 1:
                com.broadcast("elevation level:" + str(level) + ";id:" + str(com.id))
            nb_players = check_players_arrived(com.postman(), nb_players, com.id)
            food = inventaire_cmd.get_food_quantity(inventaire_cmd.inventaire(com.inventaire()))
        if com.level > 1:
            com.broadcast("elevation enough players id:" + str(com.id))
        if food <= misc.critical_food:
            com.broadcast("elevation aborted " + str(com.id))
            com.mode = 0
            print("incantation aborted")
            return False
        if check_case(level, case) == False:
            drop_on_case(com, level, case, nb_players)
        take_the_too(com, voir_cmd.voir(com.voir())[0][0])
        print(com.level, " ", voir_cmd.voir(com.voir())[0][0])
        if com.level != 1:
            tmp = "fete_du_sleep id:" + str(com.id)
            print(tmp)
            com.broadcast(tmp)
        print(food)
        print("on commence l'incantation NIVEAU :", com.level)
        ret = com.postman()
        while len(ret) > 0:
            del ret[0]
        ret = com.incantation()
        print("RETOUR DE L'INCANTATION : ", ret)
        print("incantation finie :", com.level)
        com.broadcast("incantation_finie level:" + str(com.level) + " id:" + str(com.id))
        com.mode = 0
        return True
    return False
