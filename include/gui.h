#ifndef GUI_H
#define GUI_H

#include <windows.h>

#define WM_TRAYICON (WM_USER + 1)

#define ID_TRAY_OPEN  1001
#define ID_TRAY_EXIT  1002
#define IDI_APPICON 101

int run_gui(HINSTANCE hInst);

#endif