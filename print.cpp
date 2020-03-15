#include "print.h"

#include <cstdio>

#if defined(WIN32) || defined(_WIN32)
#include <windows.h>

namespace {

bool vtModeEnabled = false;

bool enableVTMode() {
    // Set output mode to handle virtual terminal sequences
    const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) {
        return false;
    }
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) {
        return false;
    }
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) {
        return false;
    }
    return true;
}

} // namespace
#endif

void Utils::print(const wchar_t *message, Utils::TextColor textColor,
                  Utils::BackgroundColor backgroundColor) {
    if (!message) {
        return;
    }
#if defined(WIN32) || defined(_WIN32)
    if (!vtModeEnabled) {
        if (!enableVTMode()) {
            return;
        }
        vtModeEnabled = true;
    }
#endif
    const wchar_t *foregroundColors[] = {// Black
                                         L"30",
                                         // Red
                                         L"31",
                                         // Green
                                         L"32",
                                         // Yellow
                                         L"33",
                                         // Blue
                                         L"34",
                                         // Magenta
                                         L"35",
                                         // Cyan
                                         L"36",
                                         // White
                                         L"37"};
    const wchar_t *backgroundColors[] = {// Black
                                         L"40",
                                         // Red
                                         L"41",
                                         // Green
                                         L"42",
                                         // Yellow
                                         L"43",
                                         // Blue
                                         L"44",
                                         // Magenta
                                         L"45",
                                         // Cyan
                                         L"46",
                                         // White
                                         L"47"};
    wprintf(L"\x1b[1;%s;%sm%s\x1b[0m",
            foregroundColors[static_cast<int>(textColor)],
            backgroundColors[static_cast<int>(backgroundColor)], message);
}
