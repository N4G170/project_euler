#include "comparer.hpp"

bool operator==(const SDLFontParams& left, const SDLFontParams& right) { return (left.name == right.name && left.size == right.size); }
bool operator==(const FontParams& left, const FontParams& right) { return (left.name == right.name && left.size == right.size); }
