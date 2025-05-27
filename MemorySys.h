#include <windows.h>
#include <string>
#include <iomanip>
#include <vector>
#include <codecvt>

std::wstring utf8_to_utf16(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}

struct DriveInfo {
    std::string name;
    std::string type;
    uint64_t totalSize = 0;
    uint64_t freeSpaceSize = 0;
};

std::vector<std::string> GetDrivesPaths() {
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

    std::wstring widePath = utf8_to_utf16(drivePath);

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
        info.freeSpaceSize = freeBytes.QuadPart;
    }

    return info;
}

class DriveInfoNavigator {
public:
    std::string selectedName;
    std::string selectedType;
    std::string selectedTotalSize;
    std::string selectedFreeSpaceSize;

    size_t totalDrives = 0;

private:
    int32_t currentIndex = 0;

public:

    DriveInfoNavigator()
    {
        auto drivesPaths = GetDrivesPaths();
        totalDrives = drivesPaths.size();

        Update(GetDriveInfo(drivesPaths[currentIndex]));
    }

    void Next() {
        auto drivesPaths = GetDrivesPaths();
        totalDrives = drivesPaths.size();

        if (currentIndex >= totalDrives - 1)
            currentIndex = 0;
        else
            currentIndex++;

        Update(GetDriveInfo(drivesPaths[currentIndex]));
    }

    void Prev() {
        auto drivesPaths = GetDrivesPaths();
        totalDrives = drivesPaths.size();

        if (currentIndex == 0)
            currentIndex = totalDrives - 1;
        else
            currentIndex--;

        Update(GetDriveInfo(drivesPaths[currentIndex]));
    }

private:

    void Update(DriveInfo info) {
        auto driveTotalSize = (info.totalSize / 1024 / 1024 / 1024);
        auto driveFreeSpaceSize = (info.freeSpaceSize / 1024 / 1024 / 1024);

        selectedName = info.name;
        selectedType = info.type;
        selectedTotalSize = "Total: " + std::to_string(driveTotalSize) + " GB ";
        selectedFreeSpaceSize = "Free:  " + std::to_string(driveFreeSpaceSize) + " GB ";
    }
};
