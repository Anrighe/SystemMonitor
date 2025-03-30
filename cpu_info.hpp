#ifndef CPU_INFO_HPP
#define CPU_INFO_HPP

#include <QString>

class CpuInfo {

public:
    CpuInfo();
    QString getCpuName() const;
    double getCpuUsage() const;

private:
    QString cpuName;
    void loadCpuName();
};

#endif // CPU_INFO_HPP
