#!/usr/bin/python
import misc
import voir_cmd
import inventaire_cmd
import choose_an_ore
import random


OtherOre = 2
InterestingOre = OtherOre * 2
Food = 2
ActionPrice = 2
IsInterresting = 2

def find_pos_in_priority_tab(inventory_tab):
    inventory_pos = 0
    while inventory_tab[inventory_pos]["type"] != '7':
        inventory_pos += 1
    current_food = inventory_tab[inventory_pos]["nb"]
    for i in range(0, len(misc.priority_tab[0])):
        if current_food > misc.priority_tab[0][i]:
            return i
    return misc.priority_tab[0][i - 1]


def do_calcul(case, priority_level, level, inventory):
    food = int(case["food"])
    ores = 0
    for i in range(0, len(case["ores"])):
        if case["ores"][i] != '0':
            if choose_an_ore.isOreInteresting(level, inventory, case["ores"][i]):
                ores += InterestingOre
            else:
                ores += OtherOre
    food *= misc.priority_tab[1][priority_level] * Food
    ores *= misc.priority_tab[2][priority_level]
    return food + ores


def make_importance_tab(priority_level, voir_tab, level, inventory):
    result = []
    for i in range(0, len(voir_tab)):
        result.append([])
        for j in range(0, len(voir_tab[i])):
            result[i].append(do_calcul(voir_tab[i][j], priority_level, level, inventory))
    return result


def get_string_from_importance(importance_tab, x, y, action):
    tmp = ""
    command = ""
    if y < len(importance_tab):
        action1, command1 = get_string_from_importance(importance_tab, x, y + 1, action + importance_tab[y][x] - 3 * ActionPrice)
        action2, command2 = get_string_from_importance(importance_tab, x + 1, y + 1, action + importance_tab[y][x] - ActionPrice)
        action3, command3 = get_string_from_importance(importance_tab, x + 2, y + 1, action + importance_tab[y][x] - 3 * ActionPrice)
        if action1 > action2:
            action = action1 + ActionPrice
            command = command1
            tmp = "APDAPG"
        else:
            action = action2
            command = command2
            tmp = "AP"
        if action3 > action:
            action = action3 + ActionPrice
            command = command3
            tmp = "APGAPD"
    if y == len(importance_tab) - 1:
        return action, ""
    return action, tmp + command


def set_command_list(importance_tab):
    tmp = ""
    action, command = get_string_from_importance(importance_tab, 0, 0, 0)
    if command[len(command) - 1] == 'D' or command[len(command) - 1] == 'G':
        if random.randint(0, 1) == 1:
            tmp = command[:len(command) - 1]
        else:
            tmp = command
    else:
        tmp = command
    return tmp


# verifier qu'il n'y a pas de message de postman avant d'appeler importance
def importance(voir_tab, inventory_tab, level):
    priority_level = find_pos_in_priority_tab(inventory_tab)
    importance_tab = make_importance_tab(priority_level, voir_tab, level, inventory_tab)
    result = set_command_list(importance_tab)
    return result
