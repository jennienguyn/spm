#include "utils.h"
#include <string.h>

void replace(char* str, const char* old, const char* rep) {
    char buf[512];
    char* p;

    while ((p = strstr(str, old))) {
        buf[0] = 0;
        strncat(buf, str, p - str);
        strcat(buf, rep);
        strcat(buf, p + strlen(old));
        strcpy(str, buf);
    }
}

void format_filename(char* out, const char* format, const char* username) {
    SYSTEMTIME t;
    GetLocalTime(&t);

    strcpy(out, format);

    char buf[32];

    wsprintf(buf, "%02d", t.wDay);    replace(out, "dd", buf);
    wsprintf(buf, "%02d", t.wMonth);  replace(out, "MM", buf);
    wsprintf(buf, "%04d", t.wYear);   replace(out, "yyyy", buf);
    wsprintf(buf, "%02d", t.wHour);   replace(out, "HH", buf);
    wsprintf(buf, "%02d", t.wMinute); replace(out, "mm", buf);

    replace(out, "USERNAME", username);
}

int ends_with_mp4(const wchar_t* name) {
    int len = wcslen(name);
    return (len > 4 && _wcsicmp(name + len - 4, L".mp4") == 0);
}

int file_older_than(const wchar_t* path, int days) {
    FILETIME ft;
    HANDLE h = CreateFileW(
        path, GENERIC_READ,
        FILE_SHARE_READ, NULL,
        OPEN_EXISTING, 0, NULL
    );
    if (h == INVALID_HANDLE_VALUE) return 0;

    GetFileTime(h, NULL, NULL, &ft);
    CloseHandle(h);

    ULARGE_INTEGER fileTime, now;
    fileTime.LowPart = ft.dwLowDateTime;
    fileTime.HighPart = ft.dwHighDateTime;

    FILETIME nowFt;
    GetSystemTimeAsFileTime(&nowFt);
    now.LowPart = nowFt.dwLowDateTime;
    now.HighPart = nowFt.dwHighDateTime;

    ULONGLONG diff =
        (now.QuadPart - fileTime.QuadPart) / 10000000ULL;

    return diff > (ULONGLONG)days * 86400ULL;
}