#include "WindowsFileSystem.h"

#include "../../Core/Logger.h"
#include "../FileSystem.h"

namespace Simulacra
{
    void WatchWindowsDirectory(const std::filesystem::path& path, const std::function<void(void)>& callback)
    {
        HANDLE Handle;
        HANDLE Event;
        OVERLAPPED Overlapped;
        char Buffer[1024];

        // std::filesystem::path formattedPath = FormatFilepath(path);
        // std::wstring widestr = std::wstring(formattedPath.string().begin(), formattedPath.string().end());
        // const wchar_t* widecstrPath = widestr.c_str();

        Handle = CreateFileW(
            // widecstrPath,
            (wchar_t*)FormatFilepath(path).c_str(),
            FILE_LIST_DIRECTORY | GENERIC_READ,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            nullptr,
            OPEN_EXISTING,
            FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
            nullptr
        );

        if (Handle == INVALID_HANDLE_VALUE)
        {
            ConsoleError("Message: {}", GetLastError());
            return;
        }

        Event = CreateEvent(nullptr, TRUE, FALSE, nullptr);
        Overlapped.hEvent = Event;

        DWORD bytesReturned = 0;
        ReadDirectoryChangesW(
            Handle,
            &Buffer,
            sizeof(Buffer),
            TRUE,
            FILE_NOTIFY_CHANGE_LAST_WRITE,
            &bytesReturned,
            &Overlapped,
            nullptr
        );

        bool keepRunning = true;
        bool pending = false;

        do
        {
            keepRunning = ReadDirectoryChangesW(
                Handle,
                &Buffer,
                sizeof(Buffer),
                TRUE,
                FILE_NOTIFY_CHANGE_LAST_WRITE,
                &bytesReturned,
                &Overlapped,
                nullptr
            );

            HANDLE h[2] = { Overlapped.hEvent, Event };

            switch (WaitForMultipleObjects(2, h, FALSE, INFINITE))
            {
            case WAIT_OBJECT_0: {
                if (GetOverlappedResult(Handle, &Overlapped, &bytesReturned, TRUE))
                {
                    pending = false;

                    if (bytesReturned == 0)
                        break;

                    FILE_NOTIFY_INFORMATION* info = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(Buffer);
                    do 
                    {
                        if (info->Action != 0)
                        {
                            callback();
                        }

                        if (info->NextEntryOffset == 0)
                            break;

                        info = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(reinterpret_cast<BYTE*>(info) + info->NextEntryOffset);
                    }
                    while (true);
                }
                else
                {
                    ConsoleError("GetOverlappedResults failed, Message: {}", GetLastError());
                }
            } break;
            case WAIT_OBJECT_0 + 1: {
                keepRunning = false;
            } break;
            case WAIT_TIMEOUT: {
                ConsoleLog("In Timeout");
            } break;
            case WAIT_FAILED: {
                ConsoleError("WAIT_FAILED Message: {}", GetLastError());
            } break;
            case WAIT_ABANDONED: {
                ConsoleError("WAIT_ABANDONED Message: {}", GetLastError());
            } break;
            default: {
                ConsoleLog("In default");
            } break;
            }

            Overlapped.hEvent = Event;
        }
        while (keepRunning);

        if (pending)
        {
            CancelIo(Handle);
            GetOverlappedResult(Handle, &Overlapped, &bytesReturned, TRUE);
        }

        CloseHandle(Handle);
    }
}