#include "deleters.hpp"

void DestroySDLTexture (SDL_Texture* texture)
{
    //MessageWriter::Instance()->WriteLineToConsole("Calling destroy for SDL_DestroyTexture object pointer...");
    std::cout << "Calling destroy for SDL_DestroyTexture object pointer... \n";
    SDL_DestroyTexture( texture );
};
