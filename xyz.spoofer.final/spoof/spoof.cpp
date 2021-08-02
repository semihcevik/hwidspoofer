#include "spoof.h"
#include "..\bytes\bytes.hpp"
#include "..\btfile\bytetofile.hpp"
#include <direct.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

#pragma warning(disable : 4996)

#include <random>
#include <string>

template< typename ... Args >
std::string mixer(Args const& ... args)
{
    std::ostringstream stream;
    using List = int[];
    (void)List {
        0, ((void)(stream << args), 0) ...
    };
    return stream.str();
}
std::string random_string(std::string::size_type length)
{
    static auto& chrs = "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    thread_local static std::mt19937 rg{ std::random_device{}() };
    thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

    std::string s;

    s.reserve(length);

    while (length--)
        s += chrs[pick(rg)];

    return s;
}
inline bool FileExists(const std::string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}
bool IsProcessRunning(const TCHAR* executableName) {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (!Process32First(snapshot, &entry)) {
        CloseHandle(snapshot);
        return false;
    }

    do {
        if (!_tcsicmp(entry.szExeFile, executableName)) {
            CloseHandle(snapshot);
            return true;
        }
    } while (Process32Next(snapshot, &entry));

    CloseHandle(snapshot);
    return false;
}
void VanguardDrivers()
{
    system((_xor_("sc delete vgc")).c_str());
    system((_xor_("sc delete vgk")).c_str());

    remove((_xor_("%homedrive%\\Program Files\\RiotVanguard")).c_str());
    remove((_xor_("%homedrive%\\Program Files\\Riot Vanguard")).c_str());
}
void ProcessKiller() {
    if (IsProcessRunning((_xor_("steam.exe")).c_str()))
        system((_xor_("taskkill /IM steam.exe /T /F")).c_str());

    if (IsProcessRunning("steamwebhelper.exe"))
        system((_xor_("taskkill /IM steamwebhelper.exe /T /F")).c_str());

    if (IsProcessRunning((_xor_("SteamService.exe")).c_str()))
        system((_xor_("taskkill /IM SteamService.exe /T /F")).c_str());

    if (IsProcessRunning((_xor_("Origin.exe")).c_str()))
        system((_xor_("taskkill /IM Origin.exe /T /F")).c_str());

    if (IsProcessRunning((_xor_("OriginWebHelperService.exe")).c_str()))
        system((_xor_("taskkill /IM OriginWebHelperService.exe /T /F")).c_str());

    if (IsProcessRunning((_xor_("EpicGamesLauncher.exe")).c_str()))
        system((_xor_("taskkill /IM EpicGamesLauncher.exe /T /F")).c_str());

    if (IsProcessRunning((_xor_("RiotClientServices.exe")).c_str()))
        system((_xor_("taskkill /IM RiotClientServices.exe /T /F")).c_str());

    if (IsProcessRunning((_xor_("RiotClientUx.exe")).c_str()))
        system((_xor_("taskkill /IM RiotClientUx.exe /T /F")).c_str());

    if (IsProcessRunning((_xor_("RiotClientUxRender.exe")).c_str()))
        system((_xor_("taskkill /IM RiotClientUxRender.exe /T /F")).c_str());

    if (IsProcessRunning((_xor_("RiotClientCrashHandler.exe")).c_str()))
        system((_xor_("taskkill /IM RiotClientCrashHandler.exe /T /F")).c_str());

    if (IsProcessRunning((_xor_("FortniteClient-Win64-Shipping.exe")).c_str()))
        system((_xor_("taskkill /IM FortniteClient-Win64-Shipping.exe /T /F")).c_str());

    if (IsProcessRunning((_xor_("OneDrive.exe")).c_str()))
        system((_xor_("taskkill /IM OneDrive.exe /T /F")).c_str());

    if (IsProcessRunning((_xor_("RustClient.exe")).c_str()))
        system((_xor_("taskkill /IM RustClient.exe /T /F")).c_str());

    if (IsProcessRunning((_xor_("r5apex.exe")).c_str()))
        system((_xor_("taskkill /IM r5apex.exe /T /F")).c_str());

    if (IsProcessRunning((_xor_("vgtray.exe")).c_str()))
        system((_xor_("taskkill /IM vgtray.exe /T /F")).c_str());
}
void GayMacChanger() {
    std::string changer = mixer(_xor_("C:\\Windows\\System32\\Speech\\"), random_string(32), _xor_(".exe"));
    utils::CreateFileFromMemory(changer, reinterpret_cast<const char*>(gay), sizeof(gay));

    if (FileExists(changer)) {
        system(changer.c_str());
        DeleteFile(changer.c_str());
    }
}
void DriverLoad() {
    std::string finalPath = mixer(getenv("localappdata"), _xor_("\\"), random_string(32));
    // Create random string folder
    mkdir(finalPath.c_str());

    if (FileExists(finalPath)) {
        // Create gdrv.sys
        std::string gdrvRandomize = mixer(finalPath, _xor_("\\"), random_string(32), _xor_(".sys"));
        utils::CreateFileFromMemory(gdrvRandomize, reinterpret_cast<const char*>(gdrvsys), sizeof(gdrvsys));
        // Create mapper.exe
        std::string mapperRandomize = mixer(finalPath, _xor_("\\"), random_string(32), _xor_(".exe"));
        utils::CreateFileFromMemory(mapperRandomize, reinterpret_cast<const char*>(mapper), sizeof(mapper));
        // Create driver.sys
        std::string driverRandomize = mixer(finalPath, _xor_("\\"), random_string(32), _xor_(".sys"));
        utils::CreateFileFromMemory(driverRandomize, reinterpret_cast<const char*>(driversys), sizeof(driversys));

        // Checking created files
        if (FileExists(gdrvRandomize)) {
            if (FileExists(mapperRandomize)) {
                if (FileExists(driverRandomize)) {

                    // Load driver
                    std::string loadCommand = mixer(mapperRandomize, _xor_(" "), gdrvRandomize, _xor_(" "), driverRandomize);
                    system(loadCommand.c_str());

                    // Delete gdrv,mapper,driver
                    DeleteFile(mapperRandomize.c_str());
                    DeleteFile(gdrvRandomize.c_str());
                    DeleteFile(driverRandomize.c_str());
                    DeleteFile(finalPath.c_str());
                }
            }
        }
    }
}