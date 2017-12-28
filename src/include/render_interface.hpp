#ifndef RENDERINTERFACE_HPP
#define RENDERINTERFACE_HPP


#include "structs.hpp"
#include <SDL2/SDL.h>
#include <memory>

#include <string>
/**
 * \brief Basic Interface to add render behaviours to elements
 */
class RenderInterface
{
    public:
        virtual ~RenderInterface(){};

        //virtual void Render(const SDL_Rect&, const SDL_Rect&) = 0;
        virtual void Render() = 0;

//{ Region Getters/Setters
        /**
         * \brief Not yet in use
         */
        bool RenderObject() const { return m_render_object; }
        /**
         * \brief Not yet in use
         */
        void RenderObject(const bool& render_object) { m_render_object = render_object; }

        /**
         * \brief Not yet in use
         */
        bool GetZIndex() { return m_z_index; }
//}

    protected:
        /**
         * \brief Not yet in use. Will be used to turn element render on/off
         */
        bool m_render_object;

        /**
         * \brief Not yet in use. Will be used to turn element render on/off
         */
        int  m_z_index;
};

/**
 * \brief Compare struct to order render interfaces in multiset
 */
struct RenderCompare
{
    bool operator() (RenderInterface* lri, RenderInterface* rri) const
    {
        return lri->GetZIndex() < rri->GetZIndex();
    }
};
#endif // RENDERINTERFACE_HPP
