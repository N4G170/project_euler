#ifndef FONT_HPP
#define FONT_HPP

#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

#include "enums.hpp"
#include "constants.hpp"
#include "texture.hpp"
#include "structs.hpp"

class Font
{
    TTF_Font* m_font_ptr;
    SDL_Renderer* m_renderer_ptr;
    FontRenderType m_render_type;

    FontColours m_colours;

    unsigned short m_font_size;
    unsigned short m_font_break_height;

    std::string m_font_name;

    std::unordered_map<char, SDL_Texture* > m_glyphs_textures;

    public:
        /**
        *   \param[in] default_render_type can be SOLID, SHADED or BLENDED (default).
        *          \li Solid - Quick and Dirty;
        *          \li Shaded - Slow and Nice, but with a Solid Box;
        *          \li Blended - Slow Slow Slow, but Ultra Nice over another image.
        *          \n For more info go to http://jcatki.no-ip.org:8080/SDL_ttf/SDL_ttf_42.html#SEC42
        */
        Font(TTF_Font*, const FontParams&, SDL_Renderer*, FontRenderType default_render_type = FontRenderType::BLENDED);
        ~Font();

        // unsigned short FontSize() const { return m_font_size; }
        // void FontSize(const unsigned short& font_size) { m_font_size = font_size; }
        //
        // unsigned short BreakHeight() const { return m_font_break_height; }

        void CreateStringTexture(std::vector<char>&, Texture&, SDL_Point&);

        size_t CreateHash() const;

    private:
        void CreateGlyphMap();
};


#endif//FONT_HPP
