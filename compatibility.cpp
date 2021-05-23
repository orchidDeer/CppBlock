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
    #include <unistd.h>

    cKeyboard::cKeyboard() {
        active = false;
        keyboard_fd = 0;
        keyboard_ev = new input_event();
        keyboard_st = new keyboard_state();
        keyboard_fd = open(KEYBOARD_DEV, O_RDONLY | O_NONBLOCK);
        if (keyboard_fd > 0) {
            ioctl(keyboard_fd, EVIOCGNAME(256), name);
            //std::cout << "   Name: " << name << std::endl;
            active = true;
            pthread_create(&thread, 0, &cKeyboard::loop, this);
        }
    }

    void* cKeyboard::loop(void *obj) {
        while (reinterpret_cast<cKeyboard *>(obj)->active)
            reinterpret_cast<cKeyboard *>(obj)->readEv();
    }

    void cKeyboard::readEv() {
        int bytes = read(keyboard_fd, keyboard_ev, sizeof(*keyboard_ev));
        if (bytes > 0) {
            if (keyboard_ev->type & EV_KEY) {
                keyboard_st->keys[keyboard_ev->code] = keyboard_ev->value;
            }
        }
    }

    short cKeyboard::getKeyState(short key) {
        return keyboard_st->keys[key];
    }

    cKeyboard::~cKeyboard() {
        if (keyboard_fd > 0) {
            active = false;
            pthread_join(thread, 0);
            close(keyboard_fd);
        }
        delete keyboard_st;
        delete keyboard_ev;
        keyboard_fd = 0;
    }

    cKeyboard kb;

    /// Setup Linux console for use
    void setupConsole() {}

    /// Restore console
    void restoreConsole() {
        // Reset colors
        printf("\x1b[0m");
    }

    /// Gets key state for Linux
    bool getStateOfKey(int keycode) {
        return kb.getKeyState((short) keycode) > 0;
    }
#endif
