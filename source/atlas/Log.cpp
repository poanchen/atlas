#include "atlas/Platform.hpp"

#ifdef APOLLO_PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <chrono>
#include <ctime>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <vector>

#include "atlas/Log.hpp"

static const int kMaxLogLength = 16 * 1024;
static const std::vector<std::string> kLevelStrings =
std::vector<std::string>
{
    "debug",
    "info",
    "log",
    "error"
    "critical"
};


namespace atlas
{
    static void _log(std::string const& message)
    {
        char buf[kMaxLogLength];
        memcpy(buf, message.c_str(), kMaxLogLength);

#ifdef APOLLO_PLATFORM_WINDOWS
        strncat_s(buf, "\n", 3);

        WCHAR wszBuf[kMaxLogLength] = { 0 };
        MultiByteToWideChar(CP_UTF8, 0, buf, -1, wszBuf, sizeof(wszBuf));
        OutputDebugStringW(wszBuf);
        WideCharToMultiByte(CP_ACP, 0, wszBuf, -1, buf, sizeof(buf),
            nullptr, FALSE);
        printf("%s", buf);
        fflush(stdout);
#else
        strncat(buf, "\n", 3);

        fprintf(stdout, "%s", buf);
        fflush(stdout);
#endif
    }

    static std::string getTimeStamp()
    {
        auto now = std::chrono::system_clock::now();
        auto nowTime = std::chrono::system_clock::to_time_t(now);

        std::stringstream stream;
        stream << std::put_time(std::localtime(&nowTime), "%T");
        return stream.str();
    }

    void Logger::log(SeverityLevel level, std::string const& message)
    {
        std::string logMessage = "";

        // Get the current time stamp
        logMessage.append(getTimeStamp());
        logMessage.append("    ");

        std::string sevLevel = "[";
        int levelNum = static_cast<int>(level);
        sevLevel.append(kLevelStrings[levelNum]);
        sevLevel.append("] : ");

        logMessage.append(sevLevel);
        logMessage.append(message);
        _log(message);
    }
}