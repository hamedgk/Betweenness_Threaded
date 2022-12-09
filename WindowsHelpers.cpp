#include "WindowsHelpers.h"
#include <Windows.h>



int WindowsHelpers::systemCpuCount() {
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	return sysinfo.dwNumberOfProcessors;
}
