# tableau de poid des ressources en fonction du mode de recherche
# niveau de nourriture dans le 1er nourriture dans le 2eme tableau
# et minerai dans le 3eme
priority_tab = [[39, 37, 35, 33, 31, 29, 27, 25, 23, 21, 19, 17, 15, 13, 11, 9, 7, 5, 3, 0],
                [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],
                [20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1]]

# tableau contenant les ressources et un int associe
ressource_tab = [["linemate",   "1"],
                 ["deraumere",  "2"],
                 ["sibur",      "3"],
                 ["mendiane",   "4"],
                 ["phiras",     "5"],
                 ["thystame",   "6"],
                 ["nourriture", "7"],
                 ["joueur",     "8"]]

# tableaux contenant le nombre de pierres interressantes
# pour chaque lvl
lvl_ore_priority_tab1 = [{"type": "1", "nb": 1},
                         {"type": "2", "nb": 0},
                         {"type": "3", "nb": 0},
                         {"type": "4", "nb": 0},
                         {"type": "5", "nb": 0},
                         {"type": "6", "nb": 0}]

lvl_ore_priority_tab2 = [{"type": "1", "nb": 1},
                         {"type": "2", "nb": 1},
                         {"type": "3", "nb": 1},
                         {"type": "4", "nb": 0},
                         {"type": "5", "nb": 0},
                         {"type": "6", "nb": 0}]

lvl_ore_priority_tab3 = [{"type": "1", "nb": 2},
                         {"type": "2", "nb": 0},
                         {"type": "3", "nb": 1},
                         {"type": "4", "nb": 0},
                         {"type": "5", "nb": 2},
                         {"type": "6", "nb": 0}]

lvl_ore_priority_tab4 = [{"type": "1", "nb": 1},
                         {"type": "2", "nb": 1},
                         {"type": "3", "nb": 2},
                         {"type": "4", "nb": 0},
                         {"type": "5", "nb": 1},
                         {"type": "6", "nb": 0}]

lvl_ore_priority_tab5 = [{"type": "1", "nb": 1},
                         {"type": "2", "nb": 2},
                         {"type": "3", "nb": 1},
                         {"type": "4", "nb": 3},
                         {"type": "5", "nb": 0},
                         {"type": "6", "nb": 0}]

lvl_ore_priority_tab6 = [{"type": "1", "nb": 1},
                         {"type": "2", "nb": 2},
                         {"type": "3", "nb": 3},
                         {"type": "4", "nb": 0},
                         {"type": "5", "nb": 1},
                         {"type": "6", "nb": 0}]

lvl_ore_priority_tab7 = [{"type": "1", "nb": 2},
                         {"type": "2", "nb": 2},
                         {"type": "3", "nb": 2},
                         {"type": "4", "nb": 2},
                         {"type": "5", "nb": 2},
                         {"type": "6", "nb": 1}]

lvl_ore_priority_tab = [[lvl_ore_priority_tab1],
                        [lvl_ore_priority_tab2],
                        [lvl_ore_priority_tab3],
                        [lvl_ore_priority_tab4],
                        [lvl_ore_priority_tab5],
                        [lvl_ore_priority_tab6],
                        [lvl_ore_priority_tab7]]

nb_players_on_case = [1, 2, 2, 4, 4, 6, 6]

def get_func_tab(com):
    function_tab = [{"function": com.avance,        "char": 'A'},
                    {"function": com.gauche,        "char": 'D'},
                    {"function": com.droite,        "char": 'G'},
                    {"function": com.prend,   "char": 'P'}]
    return function_tab

def get_routine_tab(com):
    routine_tab = [com.search_routine_cmd,
                   com.ascend_routine_cmd,
                   com.join_routine_cmd,
                   com.wait_routine_cmd]
    return routine_tab


critical_food = 10
enough_food = 30
