#include <conio.h>
#include <regex>
#include <stdio.h>
#include <Windows.h>

int wmain(int argc, wchar_t* argv[], wchar_t*)
{
    if (2 > argc)
    {
        wprintf_s(L"Usage:\nfarexec.exe {Far executable} {parameters}\n");
    }
    else
    {
        LPTSTR p = GetCommandLine();
        std::wcmatch m {};
        if (std::regex_match(p, m, std::wregex {LR"(".*"[[:s:]](.*))"}) ||
            std::regex_match(p, m, std::wregex {LR"(.*?[[:s:]](.*))"}))
        {
            size_t size = m[1].length() + 1;
            p = static_cast<LPTSTR> (HeapAlloc(GetProcessHeap(), 0, size * sizeof(TCHAR)));
            if (p)
            {
                wcscpy_s(p, size, m[1].str().c_str());
                STARTUPINFO si {};
                si.cb = sizeof(STARTUPINFO);
                si.dwFlags = 0;
                PROCESS_INFORMATION pi;
                BOOL result = CreateProcess(
                    argv[1], p, nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE, nullptr, nullptr, &si, &pi);
                if (result)
                {
                    WaitForSingleObject(pi.hProcess, INFINITE);
                    CloseHandle(pi.hThread);
                    CloseHandle(pi.hProcess);
                }
                HeapFree(GetProcessHeap(), 0, p);
            }
        }
    }
    return 0;
}