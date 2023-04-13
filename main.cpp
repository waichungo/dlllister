#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <tlhelp32.h>
using std::string;
using std::vector;
std::vector<string> ListProcessModules(DWORD dwPID)
{
    std::vector<std::string> modules;

    HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
    MODULEENTRY32 me32;

    //  Take a snapshot of all modules in the specified process.
    hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
    if (hModuleSnap == INVALID_HANDLE_VALUE)
    {
        return modules;
    }

    //  Set the size of the structure before using it.
    me32.dwSize = sizeof(MODULEENTRY32);

    //  Retrieve information about the first module,
    //  and exit if unsuccessful
    if (!Module32First(hModuleSnap, &me32))
    {

        CloseHandle(hModuleSnap); // Must clean up the snapshot object!
        return modules;
    }

    do
    {
        modules.push_back(me32.szExePath);

    } while (Module32Next(hModuleSnap, &me32));

    CloseHandle(hModuleSnap);

    return modules;
}

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        auto processId = atoi(argv[1]);
        if (processId > 0)
        {
            auto mods=ListProcessModules(processId);
            for (auto &mod : mods)
            {
                printf("%s\n",mod.c_str());
            }
            
        }
    }
}
