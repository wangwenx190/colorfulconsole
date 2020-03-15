#pragma once

namespace Utils {

enum class TextColor { Black, Red, Green, Yellow, Blue, Magenta, Cyan, White };

using BackgroundColor = TextColor;

void print(const wchar_t *message, TextColor textColor = TextColor::White,
           BackgroundColor backgroundColor = BackgroundColor::Black);

} // namespace Utils
