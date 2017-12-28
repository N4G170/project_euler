#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <SDL2/SDL.h>
#include <memory>

#include "structs.hpp"

/**
* \brief Class that loads and stores a texture to be rendered
*/
class Texture
{
    public:
        Texture();
        /** Constructor */
        Texture(const std::string&, SDL_Renderer*);
        Texture(SDL_Surface*, SDL_Renderer*);

        /** Calls SDL_CreateTexture */
        Texture(SDL_Renderer* renderer, Uint32 format, SDL_TextureAccess access, int width, int height);

        /** Default destructor */
        virtual ~Texture();

        void ConfigTexture(const std::string&, SDL_Renderer*);
        void ConfigTexture(SDL_Surface*, SDL_Renderer*);

        /**
        * \brief Raw pointer to the SDL_Texture (needed by some SDL functions)
        */
        SDL_Texture* GetSDL_TexturePtr();

        void Render();
        void Render(const SDL_Rect&, const SDL_Rect&);
        /**
         * Render the current SDL_Texture given a source OR a destination rect
         * @param SDL_Rect with the area to be renderer, if the are is the source or the destination, depends on the next param
         * @param is_source, is the SDL_rect the source rect for the rendering or the destination
         */
        void Render(const SDL_Rect&, bool is_source = true);

        /**
        * \brief Return the size of the loaded texture
        */
        SDL_Rect Size() const { return m_size; };

    protected:

    private:
        /**
        * \brief std::unique_ptr holding the loaded texture
        */
        std::unique_ptr< SDL_Texture, Deleters > m_texture;

        /**
         * \brief Main renderer observing pointer
         */
        SDL_Renderer* m_renderer_ptr;

        /**
        * \brief The size of the loaded texture
        */
        SDL_Rect m_size;

        void LoadMedia(const std::string&);
};

#endif // TEXTURE_HPP
