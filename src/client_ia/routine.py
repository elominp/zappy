#!/usr/bin/python

import importance_tab
import voir_cmd
import process_action_list
import inventaire_cmd
import parse_msg
import elevation
import movement
import misc


def search_routine(com):
    inventory = inventaire_cmd.inventaire(com.inventaire())
    if process_action_list.check_join(com.postman(), com) and inventaire_cmd.get_food_quantity(inventory) > misc.enough_food:
        com.mode = 2
        return
    voir = voir_cmd.voir(com.voir())
    if process_action_list.check_join(com.postman(), com) and inventaire_cmd.get_food_quantity(inventory) > misc.enough_food:
        com.mode = 2
        return
    if elevation.check_elevation(com.level, inventory, voir[0][0]) and inventaire_cmd.get_food_quantity(inventory) > misc.enough_food:
        com.mode = 1
        return
    cmd_string = importance_tab.importance(voir, inventory, com.level)
    process_action_list.process_action_list(cmd_string, voir, inventory, com)


def ascend_routine(com):
    voir = voir_cmd.voir(com.voir())
    inventory = inventaire_cmd.inventaire(com.inventaire())
    elevation.elevation(com, com.level, inventory, voir[0][0])

def join_routine(com):
    action_max = 5
    nb_action = 0
    food = inventaire_cmd.get_food_quantity(inventaire_cmd.inventaire(com.inventaire()))
    while nb_action != action_max and food > misc.critical_food:
        com.voir()
        food = inventaire_cmd.get_food_quantity(inventaire_cmd.inventaire(com.inventaire()))
        msg_list = com.postman()
        msg_list.reverse()
        msg = parse_msg.parse_ascend_msg(msg_list, com.idRadio)
        if msg == -2:
            com.mode = 0  # search mode
            return 0
        elif msg > 0:
            movement.move_to_point(com, msg)
            nb_action = 0
        elif msg == 0:
            com.broadcast("joined %d" % com.idRadio)
            print("JOIN")
            com.mode = 3  # wait mode
            return 0
        elif msg == -1:
#            com.avance()
            print("nothing received")
            nb_action += 1
    com.mode = 0  # search mode


def wait_routine(com):
    print("mon id est %s" % com.id, "et j'ecoute le %d" % com.idRadio)
    food = inventaire_cmd.get_food_quantity(inventaire_cmd.inventaire(com.inventaire()))
    while food > misc.critical_food:
        food = inventaire_cmd.get_food_quantity(inventaire_cmd.inventaire(com.inventaire()))
        msg_list = com.postman()
        msg = parse_msg.parse_wait_msg(msg_list, com)
        if msg == -2:
            return 0
        if msg == 1:  # incantation commence
            msg_list = com.postman()
            msg_list.reverse()
            msg = parse_msg.parse_wait_msg(msg_list, com)
            print("Boucle d'incantation")
            while msg <= 1:  # on attend la fin de l'incantation
                msg_list = com.postman()
                msg = parse_msg.parse_wait_msg(msg_list, com)
            com.mode = 0  # search mode
            print("fin de la boucle %d" % msg)
            if msg > 1:
                print("Apres incantation level %d", com.level)
            return 0
    com.mode = 0  # search mode
    com.idRadio = 0
    com.broadcast("aborted %d" % com.idRadio)
    print("Je suis niveau %d" % com.level)


def cosmogonie(com):
    x = com.slots_available()
    while x < 12:
        com.fork()
        com.avance()
        x += 1