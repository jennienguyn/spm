#include "autostart.h"
#include <windows.h>

void set_autostart(int enable) {
    HKEY hKey;
    RegOpenKey(
        HKEY_CURRENT_USER,
        "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
        &hKey
    );

    if (enable) {
        char path[MAX_PATH];
        GetModuleFileName(NULL,path,MAX_PATH);
        RegSetValueEx(
            hKey,"SAMPProofManager",0,REG_SZ,
            (BYTE*)path,lstrlen(path)+1
        );
    } else {
        RegDeleteValue(hKey,"SAMPProofManager");
    }
    RegCloseKey(hKey);
}