#!/usr/bin/python

def item(item_string):
    tab = item_string.split(':')
    return {"type": tab[0], "nb": int(tab[1])}


def case(players, food, ores):
    return {"players": players, "food": food, "ores": ores}

def action(function, id):
    return {"function": function, "char":id}
