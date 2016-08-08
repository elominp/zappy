#!/usr/bin/python
import string

def parse_ascend_msg(msg_list, id):  # return direction to go to when in join mode
    if len(msg_list) == 0:
        return -1
    for y in range(0, len(msg_list)):
        if "fete_du_sleep id:" + str(id) in msg_list:
            return -2
        ndx = string.find(msg_list[y],"id", 0, len(msg_list[y]))
        if ndx != -1 and int(msg_list[y][ndx + 3:]) == id:
            msg = msg_list[y].split(' ')
            if msg[1][string.find(msg[1],",", 0, len(msg[1])) + 1:] == "elevation":
                while len(msg_list):
                    del msg_list[0]
                return int(msg[1][0 : string.find(msg[1],",", 0, len(msg[1]))]) if msg[2] != "aborted" else -2
            elif msg[1][string.find(msg[1],",", 0, len(msg[1])) + 1:] == "enough" and msg[2] == "players":
                while len(msg_list):
                    del msg_list[0]
                return -2
        y += 1
    return -1

def parse_wait_msg(msg_list, com):  # return 1 when ascend begins and the level when it ends
    if len(msg_list) == 0:
        return -1
    for y in range(0, len(msg_list)):
        if "niveau actuel : " in msg_list[y]:
            return int(msg_list[y][len("niveau actuel : "):])
        ndx = string.find(msg_list[y], "id:", 0, len(msg_list[y]))
        if ndx != -1 and int(msg_list[y][ndx + 3:]) == com.idRadio:
            msg = msg_list[y].split(' ')
            print(msg)
            if msg[1][string.find(msg[1],",", 0, len(msg[1])) + 1:] == "fete_du_sleep":
                del msg_list[:]
                return 1
            elif msg[1][string.find(msg[1],",", 0, len(msg[1])) + 1:] == "incantation_finie":
                ndx = string.find(msg[2], "level", 0, len(msg[2]))
                print(msg[2], ndx)
                print(msg[2][ndx:])
                level = int(msg[2].split(":")[1])
                print(level)
                del msg_list[:]
                return level
        y += 1
    return -1
