#pragma once
#include <iostream>
#include <Windows.h>
#include "..\encrypt\xor.h"
#include <tlhelp32.h>
#include <tchar.h>

void VanguardDrivers();
void ProcessKiller();
bool IsProcessRunning(const TCHAR* executableName);
void GayMacChanger();
void FileExists();
void DriverLoad();