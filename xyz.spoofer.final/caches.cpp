#include "caches.h"

void CleanCaches() {
	system(_xor_("reg delete HKLM\\SOFTWARE\\WOW6432Node\\EasyAntiCheat /f").c_str());
}