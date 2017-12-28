#ifndef COMPARER_HPP
#define COMPARER_HPP

#include <functional>
#include <string>
#include "structs.hpp"

bool operator==(const SDLFontParams& left, const SDLFontParams& right);
bool operator==(const FontParams& left, const FontParams& right);


struct EqualsToFunctions
{


    //inline bool operator==(const FontParams& left, const FontParams& right) { return (left.name == right.name && left.size == right.size); }
};

#endif //COMPARER_HPP
