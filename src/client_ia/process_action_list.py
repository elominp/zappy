#!/usr/bin/python
from misc import get_func_tab
from choose_an_ore import make_a_choice
import misc
import inventaire_cmd

def check_join(messages, com):
    i = 0
    while len(messages) > 0:
        if "elevation level" in messages[i]:
            tmp = messages[i][len("elevation "):].split(";")
            if int(tmp[0].split(":")[1]) == com.level:
                com.idRadio = int(tmp[1].split(":")[1])
                return True
        del messages[i]
    return False


def process_action_list(action_list, case_list, inventory, com):
    posX, posY, direction = 0, 0, 0
    function_tab = get_func_tab(com)
    for x in range(0, len(action_list)):
        for y in range(0, len(function_tab)):
            if check_join(com.postman(), com) and inventaire_cmd.get_food_quantity(inventory) > misc.enough_food:
                com.mode = 2
                return
            if function_tab[y]["char"] == action_list[x]:
                if function_tab[y]["char"] == 'G':
                    direction += 1
                    function_tab[y]["function"]()
                    y = len(function_tab)
                elif function_tab[y]["char"] == 'D':
                    direction -= 1
                    function_tab[y]["function"]()
                    y = len(function_tab)
                elif function_tab[y]["char"] == 'A':
                    if direction == 0:
                        posY += 1
                        posX += 1
                    elif direction > 0:
                        posX += 1
                    else:
                        posX -= 1
                    function_tab[y]["function"]()
                    y = len(function_tab)
                elif function_tab[y]["char"] == 'P':
                    if posX == 0 and posY == 0:
                        tmp_case = case_list[posY][posX]
                        tmp_case["players"] -= 1
                        make_a_choice(tmp_case, com.level, inventory, com)
                    else:
                        make_a_choice(case_list[posY][posX], com.level, inventory, com)
                    y = len(function_tab)
            y += 1
        x += 1
