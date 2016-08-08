#!/bin/bash

gcc -Wall -Wextra -I. zappy_communicator_module.c zappy_communicator.c -shared -fPIC -o zappy_communicator.so
