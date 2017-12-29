#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include "SDL.h"
#include <string>
#include "structs.hpp"

namespace Colour
{
    const SDL_Colour Black {0,0,0,255};
    const SDL_Colour White {255,255,255,255};
    const SDL_Colour Red {255,0,0,255};
    const SDL_Colour Green {0,255,0,255};
    const SDL_Colour Blue {0,0,255,255};
    const SDL_Colour Cyan {0,255,255,255};
    const SDL_Colour Yellow {255,255,0,255};
    const SDL_Colour Magenta {255,0,255,255};
    const SDL_Colour Grey {190,190,190,255};
}

namespace Path
{
    namespace Font
    {
        extern std::string DejaVuSansMono;
    }
}

namespace StateName
{
    const std::string Splash{"splash"};
    const std::string Problems{"problems"};
}

namespace TextureName
{
    namespace UI
    {
        const std::string SplashBg {"splash_bg"};
        const std::string Btn {"btn"};
        const std::string Textbox {"textbox"};
        const std::string Header {"header"};
    }
}

namespace JsonConstants
{
    const std::string TypeImage{"image"};
    const std::string TypeText{"text"};
}

namespace Defaults
{
    const SDL_Rect FullImageRect{0,0,-1,-1};
    const FontColours DefaultFontColours{ Colour::Black, Colour::White };
}

#endif //CONSTANTS_HPP
