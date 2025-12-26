#include "watcher.h"
#include "utils.h"
#include <windows.h>
#include <stdio.h>

DWORD WINAPI watch_thread(LPVOID lp) {
    AppConfig* cfg = (AppConfig*)lp;

    HANDLE dir = CreateFileW(
        (LPCWSTR)cfg->video_path,
        FILE_LIST_DIRECTORY,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS,
        NULL
    );

    if (dir == INVALID_HANDLE_VALUE)
        return 0;

    BYTE buffer[2048];
    DWORD bytes;

    while (ReadDirectoryChangesW(
        dir, buffer, sizeof(buffer), FALSE,
        FILE_NOTIFY_CHANGE_FILE_NAME,
        &bytes, NULL, NULL)) {

        FILE_NOTIFY_INFORMATION* fni =
            (FILE_NOTIFY_INFORMATION*)buffer;

        if (fni->Action == FILE_ACTION_ADDED) {

            wchar_t filename[260];
            wcsncpy(filename,
                fni->FileName,
                fni->FileNameLength / 2);
            filename[fni->FileNameLength / 2] = 0;

            if (!ends_with_mp4(filename))
                continue;

            Sleep(1500);

            wchar_t oldPath[512];
            swprintf(oldPath, 512,
                L"%S\\%s",
                cfg->video_path,
                filename);

            char newNameA[256];
            format_filename(
                newNameA,
                cfg->format,
                cfg->username
            );

            wchar_t newPath[512];
            swprintf(newPath, 512,
                L"%S\\%S",
                cfg->video_path,
                newNameA);

            MoveFileExW(
                oldPath,
                newPath,
                MOVEFILE_REPLACE_EXISTING
            );
        }

        WIN32_FIND_DATAW fd;
        wchar_t search[512];
        swprintf(search, 512,
            L"%S\\*.mp4",
            cfg->video_path);

        HANDLE hFind = FindFirstFileW(search, &fd);
        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                wchar_t path[512];
                swprintf(path, 512,
                    L"%S\\%s",
                    cfg->video_path,
                    fd.cFileName);

                if (file_older_than(path, cfg->keep_days)) {
                    DeleteFileW(path);
                }

            } while (FindNextFileW(hFind, &fd));
            FindClose(hFind);
        }
    }
    CloseHandle(dir);
    return 0;
}