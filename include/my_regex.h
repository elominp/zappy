/*
** regex.h for  in /home/querat_g/tmp/PSU_2015_myirc/src/common
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sat May 28 18:12:11 2016 querat_g
// Last update Thu Jun 16 10:24:27 2016 querat_g
*/

#ifndef REGEX_H_
# define REGEX_H_

# define COMMAND_REG    "[a-zA-Z0-9_\\-]+"

/*
** because forbidding multiline macros use to students
** gotta be cleaner, right guys ?
*/
# define HOST_REG1      "^(([a-zA-Z]|[a-zA-Z][a-zA-Z0-9\-]*"
# define HOST_REG2      "[a-zA-Z0-9])\.)*"
# define HOST_REG3      "([A-Za-z]|[A-Za-z][A-Za-z0-9\-]*[A-Za-z0-9])$"
# define HOST_REG       HOST_REG1##HOST_REG2##HOST_REG3
#endif
