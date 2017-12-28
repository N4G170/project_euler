#include "font.hpp"
#include "message_writer.hpp"
#include <SDL2/SDL.h>

Font::Font(TTF_Font* font_ptr, const FontParams& params, SDL_Renderer* renderer, FontRenderType default_render_type): m_font_ptr{font_ptr}, m_renderer_ptr{renderer}, m_render_type{default_render_type}
{
    m_colours = params.colours;
    m_font_name = params.name;

    CreateGlyphMap();
}

Font::~Font()
{
    m_font_ptr = nullptr;
    m_renderer_ptr = nullptr;
}

void Font::CreateGlyphMap()
{
    std::function<SDL_Surface*(TTF_Font*, char, FontColours)> create_glyph_surface;

    switch( m_render_type )
    {
        case FontRenderType::SOLID:
            create_glyph_surface = [](TTF_Font* font, char c, FontColours colours) -> SDL_Surface*{ return TTF_RenderGlyph_Solid( font, c, colours.foreground ); };
        break;

        case FontRenderType::SHADED:
            create_glyph_surface = [](TTF_Font* font, char c, FontColours colours) -> SDL_Surface*{ return TTF_RenderGlyph_Shaded( font, c, colours.foreground, colours.background ); };
        break;

        case FontRenderType::BLENDED:
        default:
            create_glyph_surface = [](TTF_Font* font, char c, FontColours colours) -> SDL_Surface*{ return TTF_RenderGlyph_Blended( font, c, colours.foreground ); };
        break;
    }

    for(char c{32}; c < 127; ++c)
    {
        SDL_Surface* textSurface = create_glyph_surface(m_font_ptr, c, m_colours);

        m_glyphs_textures.emplace(c, SDL_CreateTextureFromSurface(m_renderer_ptr, textSurface));

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
}

void Font::CreateStringTexture(std::vector<char>& sentence, Texture& target_texture, SDL_Point& top_left_point)
{
    //change render target to texture
    //SDL_SetRenderTarget(m_renderer_ptr, target_texture.GetSDL_TexturePtr());

    for(unsigned int i{0}; i < sentence.size(); ++i)
    {

    }

    //reset render target
    SDL_SetRenderTarget(m_renderer_ptr, NULL);
}

size_t Font::CreateHash() const
{
    return std::hash<std::string>()(m_font_name) ^ std::hash<int>()(m_font_size);
}
