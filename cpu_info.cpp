#include <windows.h>
#include "cpu_info.hpp"


CpuInfo::CpuInfo() {
    loadCpuName();
}

void CpuInfo::loadCpuName() {
    HKEY hKey;
    char value[256];
    DWORD size = sizeof(value);

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        if (RegQueryValueExA(hKey, "ProcessorNameString", nullptr, nullptr, (LPBYTE)&value, &size) == ERROR_SUCCESS) {
            cpuName = QString::fromLocal8Bit(value).trimmed();;
        } else {
            cpuName = "Unknown CPU";
        }

        RegCloseKey(hKey);
    } else {
        cpuName = "Unknown CPU";
    }
}

QString CpuInfo::getCpuName() const {
    return cpuName;
}

double CpuInfo::getCpuUsage() const {
    return 50.0;
}
