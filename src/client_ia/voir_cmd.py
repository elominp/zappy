#!/usr/bin/python
import string
from remove_substring import remove_substring
import misc
from dico import case


def init_a_case(tab):
    players = 0
    food = 0
    ores = []
    ores_pos = 0
    for i in range(0, len(tab)):
        if tab[i] == '7':
            food += 1
        elif tab[i] == '8':
            players += 1
        else:
            ores.append(tab[i])
            ores_pos += 1
    return case(players, food, ores)


def get_list_from_see(cmd_line):
    cmd_tab = cmd_line.split(",")
    for x in range(0, len(cmd_tab)):
        cmd_tab[x] = remove_substring(cmd_tab[x])
        x += 1
    for y in range(0, len(cmd_tab)):
        for x in range(0, len(misc.ressource_tab)):
            if cmd_tab[y] == "":
                cmd_tab[y] = '0'
            else:
                cmd_tab[y] = string.replace(cmd_tab[y], misc.ressource_tab[x][0], misc.ressource_tab[x][1])
            x += 1
        y += 1
    return cmd_tab


def voir(cmd):
    tmp_tab = get_list_from_see(cmd)
    result = []
    curr_length = 1
    curr_pos_tmp_list = 0
    i = 0
    while curr_pos_tmp_list < len(tmp_tab):
        result.append([])
        j = 0
        while j < curr_length:
            result[i].append(init_a_case(tmp_tab[curr_pos_tmp_list]))
            curr_pos_tmp_list += 1
            j += 1
        curr_length += 2
        i += 1
    return result
