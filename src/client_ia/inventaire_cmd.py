#!/usr/bin/python
import string
from remove_substring import remove_substring
from misc import ressource_tab
from dico import item

def get_list_from_inventory(cmd_line):
    cmd_line = string.replace(cmd_line, ", ", ",")
    cmd_tab = cmd_line.split(",")
    for x in range(0, len(cmd_tab)):
        cmd_tab[x] = string.replace(cmd_tab[x], " ", ":")
        cmd_tab[x] = remove_substring(cmd_tab[x])
        x += 1
    for y in range(0, len(cmd_tab)):
        for x in range(0, len(ressource_tab)):
            if cmd_tab[y] == "":
                cmd_tab[y] = '0'
            else:
                cmd_tab[y] = string.replace(cmd_tab[y], ressource_tab[x][0], ressource_tab[x][1])
            x += 1
        y += 1
    return cmd_tab

def inventaire(cmd):
    result = []
    tmp_tab = get_list_from_inventory(cmd)
    for i in range(0, len(tmp_tab)):
        result.append(item(tmp_tab[i]))
    return result

def get_food_quantity(inventory):
    for x in range(0, len(inventory)):
        if inventory[x]["type"] == '7':
            return inventory[x]["nb"]
        x += 1
    return 0
