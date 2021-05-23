// For compatibility between Windows and Linux

#ifdef _WIN32
    #include <windows.h>
#endif

#include <cstdio>
#include "compatibility.h"

// Windows
#ifdef _WIN32
    // Some old MinGW/CYGWIN distributions don't define this:
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
    #endif

    static HANDLE stdoutHandle;
    static DWORD outModeInit;

    /// Setup windows console to accept ANSI escape codes
    void setupConsole() {
        DWORD outMode = 0;
        stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

        if(stdoutHandle == INVALID_HANDLE_VALUE) {
            exit(int(GetLastError()));
        }

        if(!GetConsoleMode(stdoutHandle, &outMode)) {
            exit(int(GetLastError()));
        }

        outModeInit = outMode;

        // Enable ANSI escape codes
        outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

        if(!SetConsoleMode(stdoutHandle, outMode)) {
            exit(int(GetLastError()));
        }
    }

    /// Reset color and console mode
    void restoreConsole() {
        // Reset colors
        printf("\x1b[0m");

        // Reset console mode
        if(!SetConsoleMode(stdoutHandle, outModeInit)) {
            exit(int(GetLastError()));
        }
    }

    /// Gets key state for Windows
    bool getStateOfKey(int keycode) {
        if(GetKeyState(keycode) & 0x8000) {
            return true;
        }
        return false;
    }

// Linux
#else
    /// Setup Linux console for use
    void setupConsole() {}

    /// Reset color
    void restoreConsole() {
        // Reset colors
        printf("\x1b[0m");
    }

    /// TODO: Gets key state for Linux
    bool getStateOfKey(int keycode) {}
#endif