#include <windows.h>
#include <wtsapi32.h>
#include <sddl.h>
#include <stdio.h>

#pragma comment(lib, "Wtsapi32")
#pragma comment(lib, "Advapi32")

int main()
{
    DWORD count;
    LPTSTR StringSid=NULL;
    WTS_PROCESS_INFOA* ProcessInfo = NULL;
    
    BOOL process = ::WTSEnumerateProcessesA(WTS_CURRENT_SERVER_HANDLE, 0, 1, &ProcessInfo, &count);
    if (process != 0) {
        for (DWORD i = 0; i < count; i++) {
            ConvertSidToStringSid(ProcessInfo[i].pUserSid, &StringSid);
            printf("[+] PID: %u\tSession: %u\tName: %s\tSID: %ls\n", ProcessInfo[i].ProcessId, ProcessInfo[i].SessionId, ProcessInfo[i].pProcessName, StringSid);
        }
        ::WTSFreeMemory(ProcessInfo);
    }
    else
        printf("[-] %u", GetLastError());
    
    return 0;
}
