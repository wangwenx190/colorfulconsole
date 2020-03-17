#include <cwchar>

#ifdef WIN32
#include <windows.h>

#if (_WIN32_WINNT >= 0x0A00)

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

static bool win10_vtModeEnabled = false;

static void win10_enableVTMode() {
    const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    const HANDLE hErr = GetStdHandle(STD_ERROR_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }
    if (hErr != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        GetConsoleMode(hErr, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hErr, dwMode);
    }
}

#else

static WORD getForegroundColor(int color) {
    const WORD foregroundColors[] = {0,
                                     FOREGROUND_RED,
                                     FOREGROUND_GREEN,
                                     FOREGROUND_GREEN | FOREGROUND_RED,
                                     FOREGROUND_BLUE,
                                     FOREGROUND_BLUE | FOREGROUND_RED,
                                     FOREGROUND_BLUE | FOREGROUND_GREEN,
                                     FOREGROUND_BLUE | FOREGROUND_GREEN |
                                         FOREGROUND_RED};
    return foregroundColors[color];
}

static WORD getBackgroundColor(int color) {
    const WORD backgroundColors[] = {0,
                                     BACKGROUND_RED,
                                     BACKGROUND_GREEN,
                                     BACKGROUND_GREEN | BACKGROUND_RED,
                                     BACKGROUND_BLUE,
                                     BACKGROUND_BLUE | BACKGROUND_RED,
                                     BACKGROUND_BLUE | BACKGROUND_GREEN,
                                     BACKGROUND_BLUE | BACKGROUND_GREEN |
                                         BACKGROUND_RED};
    return backgroundColors[color];
}

#endif
#endif

namespace Logger {

enum class TextColor { Black, Red, Green, Yellow, Blue, Magenta, Cyan, White };

using BackgroundColor = TextColor;

enum class TextStyle { Default, Bold, Underline };

void print(const wchar_t *message, TextColor textColor = TextColor::White,
           BackgroundColor backgroundColor = BackgroundColor::Black,
           TextStyle textStyle = TextStyle::Default) {
    if (!message) {
        return;
    }
#if defined(WIN32)
#if (_WIN32_WINNT < 0x0A00)
    (void)textStyle;
    const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SecureZeroMemory(&csbi, sizeof(csbi));
    GetConsoleScreenBufferInfo(hOut, &csbi);
    const WORD originalColor = csbi.wAttributes;
    SetConsoleTextAttribute(
        hOut,
        getForegroundColor(static_cast<int>(textColor)) |
            getBackgroundColor(static_cast<int>(backgroundColor)) |
            (originalColor & 0xF0));
    fwprintf(stdout, L"%s", message);
    SetConsoleTextAttribute(hOut, originalColor);
#endif
#endif
#if !defined(WIN32) || (defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0A00))
#ifdef WIN32
    if (!win10_vtModeEnabled) {
        win10_enableVTMode();
        win10_vtModeEnabled = true;
    }
#endif
    const int textStyles[] = {0, 1, 4};
    const int foregroundColors[] = {30, 31, 32, 33, 34, 35, 36, 37};
    const int backgroundColors[] = {40, 41, 42, 43, 44, 45, 46, 47};
    fwprintf(stdout, L"\x1b[%d;%d;%dm%s\x1b[0m",
             textStyles[static_cast<int>(textStyle)],
             foregroundColors[static_cast<int>(textColor)],
             backgroundColors[static_cast<int>(backgroundColor)], message);
#endif
}

} // namespace Logger

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    Logger::print(L"Is this text black?\n", Logger::TextColor::Black);
    Logger::print(L"Is this text red?\n", Logger::TextColor::Red);
    Logger::print(L"Is this text green?\n", Logger::TextColor::Green);
    Logger::print(L"Is this text yellow?\n", Logger::TextColor::Yellow);
    Logger::print(L"Is this text blue?\n", Logger::TextColor::Blue);
    Logger::print(L"Is this text magenta?\n", Logger::TextColor::Magenta);
    Logger::print(L"Is this text cyan?\n", Logger::TextColor::Cyan);
    Logger::print(L"Is this text white?\n", Logger::TextColor::White);
    Logger::print(L"Is this background black?\n", Logger::TextColor::White,
                  Logger::BackgroundColor::Black);
    Logger::print(L"Is this background red?\n", Logger::TextColor::White,
                  Logger::BackgroundColor::Red);
    Logger::print(L"Is this background green?\n", Logger::TextColor::White,
                  Logger::BackgroundColor::Green);
    Logger::print(L"Is this background yellow?\n", Logger::TextColor::White,
                  Logger::BackgroundColor::Yellow);
    Logger::print(L"Is this background blue?\n", Logger::TextColor::White,
                  Logger::BackgroundColor::Blue);
    Logger::print(L"Is this background magenta?\n", Logger::TextColor::White,
                  Logger::BackgroundColor::Magenta);
    Logger::print(L"Is this background cyan?\n", Logger::TextColor::White,
                  Logger::BackgroundColor::Cyan);
    Logger::print(L"Is this background white?\n", Logger::TextColor::Black,
                  Logger::BackgroundColor::White);
    Logger::print(L"Is this message bold?\n", Logger::TextColor::White,
                  Logger::BackgroundColor::Black, Logger::TextStyle::Bold);
    Logger::print(L"Is this message underline?\n", Logger::TextColor::White,
                  Logger::BackgroundColor::Black, Logger::TextStyle::Underline);
    return 0;
}
