#ifndef UTILS_H
#define UTILS_H

#include <windows.h>

void format_filename(char* out, const char* format, const char* username);
int ends_with_mp4(const wchar_t* name);
int file_older_than(const wchar_t* path, int days);

#endif