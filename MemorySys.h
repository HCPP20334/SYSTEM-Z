#include <windows.h>
#include <string>
#include <iomanip>
#include <vector>
#include <codecvt>
std::wstring utf8_to_utf16(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}

// Вспомогательная функция: конвертация std::wstring (UTF-16) в std::string (UTF-8)
std::string utf16_to_utf8(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(wstr);
}
uint64_t DisksSizeCount = 0;
struct DriveInfo {
    std::string name;       // Имя диска (например, "C:\\")
    std::string type;       // Тип диска
    uint64_t totalSize;     // Общий размер (в байтах)
    uint64_t freeSpace;     // Свободное пространство (в байтах)
    uint64_t DisksSize = 0;
};
std::vector<std::string> GetLogicalDrives2() {
    std::vector<std::string> drives;
    DWORD driveMask = GetLogicalDrives();
    
    for (char drive = 'A'; drive <= 'Z'; ++drive) {
        if (driveMask & (1 << (drive - 'A'))) {
            drives.push_back(std::string(1, drive) + ":\\");
        }
    }
    return drives;
}
DriveInfo GetDriveInfo(const std::string& drivePath) {
    DriveInfo info;
    info.name = drivePath;

    // Конвертация пути в UTF-16 для Windows API
    std::wstring widePath = utf8_to_utf16(drivePath);

    // Определить тип диска
    UINT driveType = GetDriveTypeW(widePath.c_str());
    switch (driveType) {
    case DRIVE_FIXED:    info.type = "Local Drive"; break;
    case DRIVE_REMOVABLE: info.type = "Other Drive"; break;
    case DRIVE_CDROM:     info.type = "CD/DVD"; break;
    case DRIVE_REMOTE:    info.type = "Network Drive"; break;
    default:              info.type = "Unknown Drive"; break;
    }
    ULARGE_INTEGER totalBytes, freeBytes;
    if (GetDiskFreeSpaceExW(
        widePath.c_str(),
        nullptr,
        &totalBytes,
        &freeBytes
    )) {
        info.totalSize = totalBytes.QuadPart;
        info.freeSpace = freeBytes.QuadPart;
    }

    return info;
}
class DriveOffset {
public:
    uint64_t GetInfoDrive(uint64_t diskCount);
    uint64_t DisksSize = 0;
    std::string DiskName;
    std::string diskType;
    uint64_t diskTotalSize;
    uint64_t diskFreeSpace;
    std::string d0;
    std::string d1;
    std::string d2;
    std::string d3;
   // uint64_t dsk_count = 0;
    int sz = 0;
    const char* msg;
    HWND hwnd;
    std::string dr0[1024];
};


uint64_t DriveOffset::GetInfoDrive(uint64_t diskCount) {
    auto drives = GetLogicalDrives2();
    DriveOffset::DisksSize = drives.size();
    uint64_t driveid = 0;
    int sz = 0;
    for (const auto& drive : drives) {
        driveid++;
        DriveOffset::DisksSize = drives.size();
        DriveOffset::dr0[driveid] = drive;
        DriveInfo info = GetDriveInfo(DriveOffset::dr0[diskCount]);
       // std::cout << dr0[diskCount] << endl;
        DriveOffset::DiskName = info.name;
        DriveOffset::diskType = info.type;
        DriveOffset::diskTotalSize = (info.totalSize / 1024 / 1024 / 1024);
        DriveOffset::diskFreeSpace = (info.freeSpace / 1024 / 1024 / 1024);
        DriveOffset::d0 = DriveOffset::DiskName;
        DriveOffset::d1 = DriveOffset::diskType;
        DriveOffset::d2 = "Total: " + std::to_string(DriveOffset::diskTotalSize) + " GB ";
        DriveOffset::d3 = "Free:  " + std::to_string(DriveOffset::diskFreeSpace) + " GB ";
    }
    if (diskCount >= 3) {
        diskCount = 0;
    }
    
    return 0;
}
DriveOffset *DiskData = new DriveOffset;
