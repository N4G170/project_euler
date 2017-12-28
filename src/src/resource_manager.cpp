#include "resource_manager.hpp"
#include <utility>
#include "constants.hpp"
#include "font.hpp"

ResourceManager::ResourceManager()
{
    m_previous_context = m_context = ResourceManagerContext::NONE;
}

ResourceManager::~ResourceManager()
{
    //TerminateSDL();
}

bool  ResourceManager::Init(Json::Value& config_json, Json::Value& resources_json, ResourceManagerContext context)
{
    if(!InitSDL(config_json))
        return false;

    m_resource_paths = resources_json;

    ChangeManagerContext(context);

    return true;
}

void ResourceManager::ChangeManagerContext(ResourceManagerContext new_context)
{
    if(new_context == m_context)
        return;

    m_textures.clear();//clear all previous textures as we are changing textures

    m_context = new_context;

    Json::Value textures, fonts;

    //Get correct entry from json file
    switch(m_context)
    {
        case ResourceManagerContext::SPLASH:
        {
            textures = m_resource_paths["SPLASH"]["textures"];
            fonts = m_resource_paths["SPLASH"]["fonts"];
        }
        break;

        case ResourceManagerContext::PROBLEMS:
        break;

        default:
        break;
    }

    //load resources
    //textures
    for(unsigned int i{0}; i < textures.size(); ++i)
    {
        m_textures[textures[i]["key"].asString()].reset( new Texture(textures[i]["path"].asString(), m_renderer.get()) );
    }

    //fonts (TTF_Font* only)
    for(unsigned int i{0}; i < fonts.size(); ++i)
    {
        SDLFontParams params{fonts[i]["key"].asString(), fonts[i]["size"].asInt()};
        m_font_pointers[params].reset( TTF_OpenFont( fonts[i]["path"].asCString(), fonts[i]["size"].asInt() ) );
    }
}

bool ResourceManager::InitSDL(Json::Value& config_json)
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout<<"SDL could not initialize! SDL_Error: "<<SDL_GetError()<<std::endl;

        return false;
    }
    else
    {
        //Create window
        SDL_Window* window_ptr = SDL_CreateWindow( config_json["window_name"].asCString(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, config_json["window_width"].asInt(), config_json["window_height"].asInt(), SDL_WINDOW_SHOWN );
        if( window_ptr == nullptr )
        {
            std::cout<<"Window could not be created! SDL_Error: "<<SDL_GetError()<<std::endl;

            return false;
        }
        else
        {
            m_window.window.reset(window_ptr);
            m_window.window_size.x = m_window.window_size.y = 0;//for safety
            SDL_GetWindowSize(window_ptr, &m_window.window_size.w, &m_window.window_size.h);

            //Create renderer for window
            SDL_Renderer* screen_renderer_ptr = SDL_CreateRenderer( window_ptr, -1, SDL_RENDERER_ACCELERATED );

            if( screen_renderer_ptr == nullptr )
            {
                std::cout<<"Renderer could not be created! SDL Error: "<<SDL_GetError()<<std::endl;

                return false;
            }
            else
            {
                m_renderer.reset(screen_renderer_ptr);

                //Initialize renderer color
                //SDL_SetRenderDrawColor( screen_renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_SetRenderDrawColor( m_renderer.get(), 0x98, 0x25, 0x00, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    std::cout<<"SDL_image could not initialize! SDL_image Error: "<<IMG_GetError()<<std::endl;

                    return false;
                }
                else//init fonts
                {
                    //Initialize SDL_ttf
                    if( TTF_Init() == -1 )
                    {
                       std::cout<<"SDL_ttf could not initialize! SDL_ttf Error: "<< TTF_GetError()<<std::endl;
                       return false;
                    }
                }
            }
        }
    }

    return true;
}

void ResourceManager::TerminateSDL()
{
    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void ResourceManager::Terminate()
{
    /** KEEP THIS TERMINATION ORDER */
    //clear all pointers
    m_textures.clear();
    m_fonts.clear();
    m_font_pointers.clear();

    m_renderer.reset();
    m_window.window.reset();

    TerminateSDL();
}

//<f> FONTS

Font* ResourceManager::GetFontPtr(const FontParams& params)
{
    auto iterator = m_fonts.find(params);
    if(iterator != m_fonts.end())
        return iterator->second.get();

    //create new font
    SDLFontParams sdl_font_params{params.name, params.size};

    auto ttf_iterator = m_font_pointers.find(sdl_font_params);
    if(ttf_iterator != m_font_pointers.end())
    {
        auto result = m_fonts.emplace( std::make_pair(params, new Font(ttf_iterator->second.get(), params, m_renderer.get())) );

        if(result.second)
            return result.first->second.get();
        else
            return nullptr;//TODO: add log error message

        //return &m_fonts[params];
    }
    
    return nullptr;
}

Font* ResourceManager::GetFontPtr(const std::string& name, const int& size, const FontColours& colours)
{
    FontParams params{name, size, colours};
    return GetFontPtr(params);
}

//</f>
