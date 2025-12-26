#include "config.h"
#include <windows.h>
#include <string.h>

void load_config(AppConfig* cfg) {
    GetPrivateProfileString("general","video_path","",
        cfg->video_path,260,CONFIG_FILE);

    cfg->keep_days = GetPrivateProfileInt(
        "general","keep_days",14,CONFIG_FILE);

    cfg->autostart = GetPrivateProfileInt(
        "general","autostart",0,CONFIG_FILE);

    GetPrivateProfileString("general","format",
        "dd-MM-yyyy-HH-mm-USERNAME.mp4",
        cfg->format,128,CONFIG_FILE);

    GetPrivateProfileString("general","username",
        "Player",cfg->username,64,CONFIG_FILE);
}

void save_config(AppConfig* cfg) {
    char buf[16];

    WritePrivateProfileString(
        "general","video_path",cfg->video_path,CONFIG_FILE);

    wsprintf(buf,"%d",cfg->keep_days);
    WritePrivateProfileString(
        "general","keep_days",buf,CONFIG_FILE);

    wsprintf(buf,"%d",cfg->autostart);
    WritePrivateProfileString(
        "general","autostart",buf,CONFIG_FILE);

    WritePrivateProfileString(
        "general","format",cfg->format,CONFIG_FILE);

    WritePrivateProfileString(
        "general","username",cfg->username,CONFIG_FILE);
}