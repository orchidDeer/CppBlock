#pragma once

/// Setup console for Windows or Linux
void setupConsole();

/// Reset console for Windows or Linux
void restoreConsole();

/// Gets key state for Windows or TODO: Linus
bool getStateOfKey(int keycode);