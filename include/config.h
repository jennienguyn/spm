#ifndef CONFIG_H
#define CONFIG_H

#define CONFIG_FILE "config.ini"

typedef struct {
    char video_path[260];
    int keep_days;
    int autostart;
    char format[128];
    char username[64];
} AppConfig;

void load_config(AppConfig* cfg);
void save_config(AppConfig* cfg);

#endif