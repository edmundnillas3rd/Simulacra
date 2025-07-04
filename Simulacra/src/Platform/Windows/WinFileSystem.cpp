#include "WinFileSystem.h"

#include "../../Core/Logger.h"

namespace Simulacra
{
    FileHandle WatchWindowsDirectory(const std::filesystem::path& path)
    {
        FileHandle fileHandle;

        HANDLE changeHandles;
        TCHAR drive[4];
        TCHAR file[_MAX_FNAME];
        TCHAR ext[_MAX_EXT];

        _splitpath_s(path.string().c_str(), drive, 4, nullptr, 0, file, _MAX_FNAME, ext, _MAX_EXT);

        drive[2] = (TCHAR)'\\';
        drive[3] = (TCHAR)'\0';

        changeHandles = FindFirstChangeNotification(path.string().c_str(), FALSE, FILE_NOTIFY_CHANGE_LAST_WRITE);

        if (changeHandles == INVALID_HANDLE_VALUE)
        {
            ConsoleError("FindFirstChangeNotification function failed: {}", GetLastError());
            return {0};
        }

        if (changeHandles == nullptr)
        {
            ConsoleError("Unexpected nullptr from FindFirstChangeNotification.", GetLastError());
            return {0};
        }

        fileHandle.Handle = changeHandles;
        return fileHandle;
    }

    bool CheckWindowsDirectoryChanges(FileHandle handle)
    {
        handle.WaitStatus = WaitForMultipleObjects(1, &handle.Handle, FALSE, 0);
        switch (handle.WaitStatus)
        {
        case WAIT_OBJECT_0: {
            if (FindNextChangeNotification(handle.Handle) == FALSE)
            {
                ConsoleError("FindNextChangeNotification function failed: {}", GetLastError());
                return false;
            }
            return true;
        } break;
        case WAIT_TIMEOUT: {
            return false;
        } break;
        default: {
            return false;
        } break;
        }
    }
}