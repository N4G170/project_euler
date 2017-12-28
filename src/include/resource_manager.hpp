#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <string>

#include "structs.hpp"
#include "enums.hpp"
#include "json.h"//jsoncpp
#include "texture.hpp"
#include "structs.hpp"
#include "hash.hpp"
#include "comparer.hpp"

class Font;
//class Texture;

class ResourceManager
{
    ResourceManagerContext m_context;
    ResourceManagerContext m_previous_context;
    std::unordered_map<std::string, std::unique_ptr<Texture> > m_textures;
    //std::unordered_map<std::string, std::string> m_resource_paths;
    Json::Value m_resource_paths;

    //SDL Resources
    Window m_window;
    SDL_Rect m_window_size;//to avoid new polling
    std::unique_ptr<SDL_Renderer, Deleters>  m_renderer;

    /**
     * Map with font name and size as keys
     * We are unable to change the font size of a previously loaded font
     */
    std::unordered_map< SDLFontParams, std::unique_ptr<TTF_Font, Deleters>, HashFunctions > m_font_pointers;

    //TODO: change Font to std::unique_ptr<Font>, needs a new HashFunction
    std::unordered_map< FontParams, std::unique_ptr<Font>, HashFunctions > m_fonts;


    /**
     * \brief Initializes ALL SDL subsystems that will be used
     * \details Initializes SDL, SDL_image, SDL_ttf, if it fails "kills" the application
     * \return Whether all subsystems initialized correctly or at least one failed
     */
    bool InitSDL(Json::Value& config_json);

    void TerminateSDL();

    public:
        ResourceManager();
        ~ResourceManager();

        /**
         * \brief Initialize the resource manager
         * \param config_json    json file with the basic configuration
         * \param resources_json json file with the list of resources to be loaded and their respective context
         * \param context        first context to be loaded
         */
        bool Init(Json::Value& config_json, Json::Value& resources_json, ResourceManagerContext context);
        void Terminate();

        Texture* GetTexture(const std::string& texture_name) { return m_textures[texture_name] ? m_textures[texture_name].get() : nullptr; }

        SDL_Renderer* GetRendererPtr() const { return m_renderer.get(); }
        SDL_Rect GetWindowsSize() const { return m_window.window_size; }
        SDL_Window* GetWindowPtr() const { return m_window.window.get(); }

        //define manager context
        void ChangeManagerContext(ResourceManagerContext new_context);

        //fonts
        Font* GetFontPtr(const FontParams&);
        Font* GetFontPtr(const std::string&, const int&, const FontColours&);
};

//
//extern ResourceManager resource_manager;//variable defined in main.cpp

#endif//RESOURCE_MANAGER_HPP
