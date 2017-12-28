#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <memory>
#include <string>

#include "render_interface.hpp"
#include "resource_manager.hpp"

/**
 * \brief Base class for any element, to be something like GameObject in Unity3d (although its far from it, for now)
 */
class Image : public RenderInterface
{
    public:
        /** Default constructor */
        Image();
        /** Default destructor */
        virtual ~Image();

        /**
         * \param ResourceManager* - raw pointer to main resource manger
         * \param const Json::Value& - image data from saved json file
         */
        Image(ResourceManager*, const Json::Value&);

        /**
         * \param ResourceManager* - raw pointer to main resource manger
         * \param const std::string& - texture name
         * \param const SDL_Rect& - source sdl_rect
         * \param const SDL_Rect& - destination sdl_rect
         * \param const int& - z index
         */
        Image(ResourceManager*, const std::string&, const SDL_Rect&, const SDL_Rect&, const int&);

        /**
         * \brief Render current texture, based on the source and destination sdl_rects
         */
        virtual void Render();

    protected:
        ResourceManager* m_resource_manager_ptr;
        Texture* m_texture_ptr;
        SDL_Rect m_source_rect;
        SDL_Rect m_destination_rect;
};

#endif // OBJECT_HPP
