#include <iostream>
#include <windows.h>

using namespace std;


class Log {
public:
//    const int Log_Info_Level = 0;
//    const int Log_Warning_Level = 1;
//    const int Log_Error_Level = 2;

    enum Log_Level {
        Log_Info_Level,
        Log_Warning_Level,
        Log_Error_Level
    };
    Log_Level m_log_level = Log_Info_Level;

    void printInfo(const char *message) {
        if (m_log_level <= Log_Info_Level)
            cout << "[INFO:]" << message << endl;
    }

    void printWarning(const char *message) {
        if (m_log_level <= Log_Warning_Level)
            cout << "[Warning:]" << message << endl;
    }

    void printError(const char *message) {
        if (m_log_level <= Log_Error_Level)
            cout << "[Error:]" << message << endl;
    }
};


