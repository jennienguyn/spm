#include <windows.h>
#include "gui.h"
#include "watcher.h"
#include "config.h"

int WINAPI WinMain(
    HINSTANCE hInst,HINSTANCE,LPSTR,int) {

    AppConfig cfg;
    load_config(&cfg);

    CreateThread(
        NULL,0,
        watch_thread,
        &cfg,0,NULL
    );

    return run_gui(hInst);
}