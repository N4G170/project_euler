#include "texture.hpp"
#include <SDL2/SDL_image.h>

#include <iostream>

Texture::Texture()
{
    m_texture.reset();
}

Texture::Texture(const std::string& file_path, SDL_Renderer* renderer)
{
    ConfigTexture(file_path, renderer);
}

Texture::Texture(SDL_Surface* surface, SDL_Renderer* renderer)
{
    ConfigTexture(surface, renderer);
}

/** Calls SDL_CreateTexture */
Texture::Texture(SDL_Renderer* renderer, Uint32 format, SDL_TextureAccess access, int width, int height)
{
    m_renderer_ptr = renderer;

    m_texture.reset( SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height) );

    m_size.x = m_size.y = 0;
    m_size.w = width;
    m_size.h = height;
}

Texture::~Texture()
{
    //As m_texture is a unique_ptr, its deletion is taken care of by the specific deleter in the file "deleters.hpp"
    m_renderer_ptr = nullptr;//as it is an observer we do no delete it
}

void Texture::ConfigTexture(const std::string& file_path, SDL_Renderer* renderer)
{
    m_renderer_ptr = renderer;

    m_texture.reset();

    LoadMedia(file_path);
}

void Texture::ConfigTexture(SDL_Surface* surface, SDL_Renderer* renderer)
{
    m_renderer_ptr = renderer;

    m_texture.reset();

    //Create texture from surface pixels
    m_texture.reset(SDL_CreateTextureFromSurface( m_renderer_ptr, surface ));
    if( !m_texture )
    {
        std::cout<< "Unable to create texture from preloaded surface! SDL Error: "<< SDL_GetError()<<std::endl;
    }

    m_size.x = m_size.y = 0;
    m_size.w = surface->w;
    m_size.h = surface->h;

}

void Texture::LoadMedia(const std::string& file_path)
{
    //Load image at specified file_path
	SDL_Surface* loadedSurface = IMG_Load( file_path.c_str() );
	if( loadedSurface == NULL )
	{
		std::cout<< "Unable to load image "<< file_path  << "! SDL_image Error: "<< IMG_GetError()<<std::endl;
	}
	else
	{
		//Create texture from surface pixels
        m_texture.reset(SDL_CreateTextureFromSurface( m_renderer_ptr, loadedSurface ));
		if( !m_texture )
		{
		    std::cout<< "Unable to create texture from "<< file_path  << "! SDL Error: "<< SDL_GetError()<<std::endl;
		}

        m_size.x = m_size.y = 0;
        m_size.w = loadedSurface->w;
        m_size.h = loadedSurface->h;

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
}

void Texture::Render()
{
    if(m_texture)
    {
        SDL_RenderCopy( m_renderer_ptr, m_texture.get(), NULL, NULL );
    }
}

void Texture::Render(const SDL_Rect &source, const SDL_Rect &destination)
{
    if(m_texture)
    {
        SDL_RenderCopy( m_renderer_ptr, m_texture.get(), &source, &destination );
    }
}

void Texture::Render(const SDL_Rect& rect, bool is_source)
{
    if(m_texture)
    {
        if(is_source)
            SDL_RenderCopy( m_renderer_ptr, m_texture.get(), &rect, NULL );
        else
            SDL_RenderCopy( m_renderer_ptr, m_texture.get(), NULL, &rect );
    }
}
