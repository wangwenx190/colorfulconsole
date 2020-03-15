#include "print.h"

int main() {
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
    return 0;
}
