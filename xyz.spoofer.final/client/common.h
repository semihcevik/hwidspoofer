#pragma once
#include "..\encrypt\xor.h"
#include <tchar.h>
#include <iostream>
#ifdef _DEBUG
#define DEBUGLOG(msg) std::cout << msg << std::endl;   
#else
#define DEBUGLOG(msg)
#endif 