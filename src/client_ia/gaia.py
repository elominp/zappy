#!/usr/bin/python
import sys
from communicator import Communicator
import misc

def usage():
    print("Usage: python zappy_ia -n <team name> -p <port number> -h <machine name, by default local>")


# On get les opts
def check_opt():
    flag = 0
    _team = None
    _port = None
    _host = None
    for i in range(1, len(sys.argv)):
        if sys.argv[i] == '-n':
            flag = 1
        elif sys.argv[i] == '-p':
            flag = 2
        elif sys.argv[i] == '-h':
            flag = 3
        elif flag == 1:
            _team = sys.argv[i]
            flag = 0
        elif flag == 2:
            _port = int(sys.argv[i])
            flag = 0
        elif flag == 3:
            _host = sys.argv[i]
            flag = 0
        i += 1
    if _port is None or _team is None:
        usage()
        sys.exit(1)
    if _host is None:
        _host = 'localhost'
    return _host, _port, _team


def check_return_values(val):
    return False if (val is None or val is False or val == '' or val == 'ko' or val == 'mort') else True


if __name__ == "__main__":
    host, port, team = check_opt()
    com = Communicator()
    com.connect(host, port)
    print(com.join_team(team))
    routine_tab = misc.get_routine_tab(com)
    com.mode = 0
    com.cosmogonie_cmd()
    try:
        while com.alive():
            routine_tab[com.mode]()
    except Exception as e:
        print(e.message)