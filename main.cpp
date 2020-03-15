#include <cwchar>

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

namespace Utils {

enum class TextColor { Black, Red, Green, Yellow, Blue, Magenta, Cyan, White };

using BackgroundColor = TextColor;

enum class TextStyle { Default, Bold, Underline };

int print(const wchar_t *message, TextColor textColor = TextColor::White,
          BackgroundColor backgroundColor = BackgroundColor::Black,
          TextStyle textStyle = TextStyle::Default) {
    if (!message) {
        return -1;
    }
#if defined(WIN32) || defined(_WIN32)
    if (!vtModeEnabled) {
        if (!enableVTMode()) {
            return -1;
        }
        vtModeEnabled = true;
    }
#endif
    const int textStyles[] = {0, 1, 4};
    const int foregroundColors[] = {30, 31, 32, 33, 34, 35, 36, 37};
    const int backgroundColors[] = {40, 41, 42, 43, 44, 45, 46, 47};
    return wprintf(
        L"\x1b[%d;%d;%dm%s\x1b[0m", textStyles[static_cast<int>(textStyle)],
        foregroundColors[static_cast<int>(textColor)],
        backgroundColors[static_cast<int>(backgroundColor)], message);
}

} // namespace Utils

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    Utils::print(L"Is this text black?\n", Utils::TextColor::Black);
    Utils::print(L"Is this text red?\n", Utils::TextColor::Red);
    Utils::print(L"Is this text green?\n", Utils::TextColor::Green);
    Utils::print(L"Is this text yellow?\n", Utils::TextColor::Yellow);
    Utils::print(L"Is this text blue?\n", Utils::TextColor::Blue);
    Utils::print(L"Is this text magenta?\n", Utils::TextColor::Magenta);
    Utils::print(L"Is this text cyan?\n", Utils::TextColor::Cyan);
    Utils::print(L"Is this text white?\n", Utils::TextColor::White);
    Utils::print(L"Is this background black?\n", Utils::TextColor::White,
                 Utils::BackgroundColor::Black);
    Utils::print(L"Is this background red?\n", Utils::TextColor::White,
                 Utils::BackgroundColor::Red);
    Utils::print(L"Is this background green?\n", Utils::TextColor::White,
                 Utils::BackgroundColor::Green);
    Utils::print(L"Is this background yellow?\n", Utils::TextColor::White,
                 Utils::BackgroundColor::Yellow);
    Utils::print(L"Is this background blue?\n", Utils::TextColor::White,
                 Utils::BackgroundColor::Blue);
    Utils::print(L"Is this background magenta?\n", Utils::TextColor::White,
                 Utils::BackgroundColor::Magenta);
    Utils::print(L"Is this background cyan?\n", Utils::TextColor::White,
                 Utils::BackgroundColor::Cyan);
    Utils::print(L"Is this background white?\n", Utils::TextColor::Black,
                 Utils::BackgroundColor::White);
    Utils::print(L"Is this message bold?\n", Utils::TextColor::White,
                 Utils::BackgroundColor::Black, Utils::TextStyle::Bold);
    Utils::print(L"Is this message underline?\n", Utils::TextColor::White,
                 Utils::BackgroundColor::Black, Utils::TextStyle::Underline);
    return 0;
}
