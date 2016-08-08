#!/usr/bin/python

def move_to_point(com, flag):
    if flag == 1 or flag == 2 or flag == 8:
        print("avance")
        com.avance()
    elif flag >= 4 and flag <= 6:
        print("demi tour")
        com.droite()
        com.droite()
    elif flag == 3:
        print("gauche")
        com.gauche()
    elif flag == 7:
        print("droite")
        com.droite()
