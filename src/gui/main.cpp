#include "zappyui.h"
#include <QApplication>
#ifdef __WIN32
# include <windows.h>
# include <winsock2.h>
# include <ws2tcpip.h>
#endif
#include <iostream>
#include "ZappyLauncher/launcher.h"
#include "intro.h"

int main(int argc, char *argv[])
{
#ifdef __WIN32
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSADATA wsaData;
    WSAStartup(wVersionRequested, &wsaData);
#endif
    QApplication a(argc, argv);
   int return_value;
    try
    {
        Launcher launcher;
        launcher.show();
        return_value = a.exec();
    }
    catch (std::runtime_error)
    {
        return 0;
    }

    return return_value;
}
