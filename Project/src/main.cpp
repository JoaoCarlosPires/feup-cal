#include <iostream>
#include "Menu.h"

// The following includes are only needed
// if the O.S. is Windows
#ifdef _WIN32
#include <winnls.h>
#include <io.h>
#include <windows.h>
#endif

int main() {

    // If in the Windows Operating System,
    // defines the console output encoding as UTF8
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    Menu* menu = new Menu();
    menu->run();
    return 0;
}