#ifndef DELETERS_HPP
#define DELETERS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

/**
* \brief Struct defining custom destruction rules that are needed by some unique_ptrs
*/
struct Deleters
{
    void operator() (SDL_Window* window)
    {
        //MessageWriter::Instance()->WriteLineToConsole("Calling destroy for SDL_window object pointer...");
        std::cout << "Calling destroy for SDL_window object pointer... \n";
        SDL_DestroyWindow(window);
    }

    void operator() (SDL_Renderer* screen_renderer)
    {
        //MessageWriter::Instance()->WriteLineToConsole("Calling destroy for SDL_Renderer object pointer...");
        std::cout << "Calling destroy for SDL_Renderer object pointer... \n";
        SDL_DestroyRenderer(screen_renderer);
    }

    void operator() (SDL_Texture* texture)
    {
        //MessageWriter::Instance()->WriteLineToConsole("Calling destroy for SDL_DestroyTexture object pointer...");
        std::cout << "Calling destroy for SDL_DestroyTexture object pointer... \n";
        SDL_DestroyTexture( texture );
    }

    void operator() (TTF_Font* font)
    {
        //MessageWriter::Instance()->WriteLineToConsole("Calling destroy for TTF_Font object pointer...");
        std::cout << "Calling destroy for TTF_Font object pointer... \n";
        TTF_CloseFont( font );
    }
};

void DestroySDLTexture (SDL_Texture* texture);

#endif
