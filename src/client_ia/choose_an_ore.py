#!/usr/bin/python
import misc
import importance_tab


def isOreInteresting(lvl, list, ore):
    for x in range(0, len(misc.lvl_ore_priority_tab[lvl - 1][0])):
        if misc.lvl_ore_priority_tab[lvl - 1][0][x]["type"] == ore:
            for y in range(0, len(list)):
                if list[y]["type"] == ore:
                    return list[y]["nb"] < misc.lvl_ore_priority_tab[lvl - 1][0][x]["nb"]
                y += 1
        x += 1
    return False


def check_interest_for_level(case, level, inventory):
    for i in range(0, len(case["ores"])):
        if isOreInteresting(level, inventory, case["ores"][i]):
            return True
    return False


def find_for_a_level(case, level, inventory):
    for i in range(0, len(case["ores"])):
        if isOreInteresting(level, inventory, case["ores"][i]):
            return case["ores"][i]


def choose_an_ore(case, level, inventory):
    for current_level in range(level, 8):
        if check_interest_for_level(case, current_level, inventory):
            return find_for_a_level(case, current_level, inventory)
    return "0"


def make_a_choice(case, level, inventory, com):
    if case["players"] > 0:
        return
    ore = choose_an_ore(case, level, inventory)
    priority_level = importance_tab.find_pos_in_priority_tab(inventory)
    valueOre = 0
    if ore != "0" and isOreInteresting(level, inventory, ore):
        valueOre = importance_tab.InterestingOre * misc.priority_tab[2][priority_level]
    elif ore != "0":
        valueOre = importance_tab.OtherOre * misc.priority_tab[2][priority_level]
    valueFood = 0
    if case["food"] > 0:
        valueFood =  misc.priority_tab[1][priority_level] * importance_tab.Food
    while valueFood > importance_tab.IsInterresting or valueOre > importance_tab.IsInterresting:
        if valueOre > 0:
            com.prend(misc.ressource_tab[int(ore) - 1][0])
            i = 0
            boucle = True
            while i < len(case["ores"]) and boucle:
                if case["ores"][i] == ore:
                    del case["ores"][i]
                    i -= 1
                    boucle = False
                i += 1
        else:
            com.prend("nourriture")
            case["food"] -= 1
        ore = choose_an_ore(case, level, inventory)
        priority_level = importance_tab.find_pos_in_priority_tab(inventory)
        valueOre = 0
        if ore != "0" and isOreInteresting(level, inventory, ore):
            valueOre = importance_tab.InterestingOre * misc.priority_tab[2][priority_level]
        elif ore != "0":
            valueOre = importance_tab.OtherOre * misc.priority_tab[2][priority_level]
        valueFood = 0
        if case["food"] > 0:
            valueFood = misc.priority_tab[1][priority_level] * importance_tab.Food
