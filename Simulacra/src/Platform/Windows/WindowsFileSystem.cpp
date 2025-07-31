#include "WindowsFileSystem.h"

#include "../../Core/Logger.h"
#include "../FileSystem.h"

namespace Simulacra
{
    ObserveData CreateWindowsFileHandle(const std::filesystem::path& path)
    {
        ObserveData data;
        HANDLE Handle;
        HANDLE Event;

        Handle = CreateFileW(
            (wchar_t*)path.c_str(),
            FILE_LIST_DIRECTORY | GENERIC_READ,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            nullptr,
            OPEN_EXISTING,
            FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
            nullptr
        );

        if (Handle == INVALID_HANDLE_VALUE)
        {
            SIMULACRA_ERROR("Message: {}", GetLastError());
            return {0};
        }

        Event = CreateEvent(nullptr, TRUE, FALSE, nullptr);

        data.Event = Event;
        data.Handle = Handle;

        return data;
    }

    void WatchWindowsDirectory(const ObserveData& data, const std::function<void(void)>& callback)
    {
        DWORD bytesReturned = 0;
        OVERLAPPED Overlapped{0};
        char Buffer[1024 * 64];
        bool keepRunning = true;
        bool pending = false;

        Overlapped.hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);

        HANDLE h[2] = { Overlapped.hEvent, data.Event };

        do
        {
            pending = ReadDirectoryChangesW(
                data.Handle,
                &Buffer,
                sizeof(Buffer),
                TRUE,
                FILE_NOTIFY_CHANGE_LAST_WRITE,
                &bytesReturned,
                &Overlapped,
                nullptr
            );


            switch (WaitForMultipleObjects(2, h, FALSE, INFINITE))
            {
            case WAIT_OBJECT_0: {
                if (GetOverlappedResult(data.Handle, &Overlapped, &bytesReturned, TRUE))
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
                    SIMULACRA_ERROR("GetOverlappedResults failed, Message: {}", GetLastError());
                }
            } break;
            case WAIT_OBJECT_0 + 1: {
                keepRunning = false;
            } break;
            case WAIT_TIMEOUT: {
                SIMULACRA_LOG("In Timeout");
            } break;
            case WAIT_FAILED: {
                SIMULACRA_ERROR("WAIT_FAILED Message: {}", GetLastError());
            } break;
            case WAIT_ABANDONED: {
                SIMULACRA_ERROR("WAIT_ABANDONED Message: {}", GetLastError());
            } break;
            default: {
                SIMULACRA_ERROR("In default");
            } break;
            }
        }
        while (keepRunning);

        if (pending)
        {
            CancelIo(data.Handle);
            GetOverlappedResult(data.Handle, &Overlapped, &bytesReturned, TRUE);
        }

        CloseHandle(Overlapped.hEvent);
    }

    void CloseWatchWindowsDirectory(const ObserveData& data)
    {
        SetEvent(data.Event);
    }
}