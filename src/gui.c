#include "gui.h"
#include "config.h"
#include "autostart.h"

#include <shellapi.h>

static AppConfig cfg;
NOTIFYICONDATA nid;

void tray_add(HWND hwnd) {
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_TRAYICON;
    nid.hIcon = LoadIcon(NULL, IDI_APPLICATION); // icon
    lstrcpy(nid.szTip, "SAMP Proof Manager");

    Shell_NotifyIcon(NIM_ADD, &nid);
}

void tray_menu(HWND hwnd) {
    POINT p;
    GetCursorPos(&p);

    HMENU hMenu = CreatePopupMenu();
    InsertMenu(hMenu, 0, MF_BYPOSITION, ID_TRAY_OPEN, "Open Settings");
    InsertMenu(hMenu, 1, MF_BYPOSITION, ID_TRAY_EXIT, "Exit");

    SetForegroundWindow(hwnd);
    TrackPopupMenu(
        hMenu,
        TPM_BOTTOMALIGN | TPM_LEFTALIGN,
        p.x, p.y,
        0, hwnd, NULL
    );
    DestroyMenu(hMenu);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM w, LPARAM l) {

    switch (msg) {

    case WM_CREATE:
        tray_add(hWnd);
        ShowWindow(hWnd, SW_HIDE);
        break;

    case WM_TRAYICON:
        if (l == WM_RBUTTONUP) {
            tray_menu(hWnd);
        }
        else if (l == WM_LBUTTONDBLCLK) {
            ShowWindow(hWnd, SW_SHOW);
            SetForegroundWindow(hWnd);
        }
        break;

    case WM_COMMAND:
        switch (LOWORD(w)) {
        case ID_TRAY_OPEN:
            ShowWindow(hWnd, SW_SHOW);
            SetForegroundWindow(hWnd);
            break;

        case ID_TRAY_EXIT:
            tray_remove();
            PostQuitMessage(0);
            break;
        }
        break;

    case WM_CLOSE:
        ShowWindow(hWnd, SW_HIDE);
        return 0;

    case WM_DESTROY:
        tray_remove();
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, msg, w, l);
}

int run_gui(HINSTANCE hInst) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "SPM";

    RegisterClass(&wc);

    CreateWindow(
        "SPM",
        "SAMP Proof Manager",
        WS_OVERLAPPEDWINDOW|WS_VISIBLE,
        200,200,420,300,
        NULL,NULL,hInst,NULL
    );

    MSG msg;
    while (GetMessage(&msg,NULL,0,0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}