#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <mutex>

#include "structs.hpp"
#include "render_interface.hpp"
#include "font.hpp"
#include "json.h"
#include "texture.hpp"
#include "resource_manager.hpp"
#include "image.hpp"

/**
 * \brief Class rendering and controlling a text box
 * \details Currently this class is a little mess, mainly because the wrap function is not working for text rendering,
 * so to have output, I had to find an alternative to it, and this was the result.
 * As I am studying how to correctly implement a spritesheet based text rendering, to replace the current method (only for dynamic text)
 * this class will be heavly modified
 */
class TextBox : public RenderInterface
{
    public:
        /**
         * \param ResourceManager* - raw pointer to main resource manager
         * \param Json::Value - json with the configuration for this text box
         */
        TextBox(ResourceManager*, const Json::Value&);

        /** Default destructor */
        virtual ~TextBox();

        /**
         * \brief Gets the std::string text being rendered
         */
        std::string Text() const { return m_text; };
        /**
         * \brief Sets the std::string text being rendered
         */
        void Text(const std::string&);

        /**
         * \brief Appends the new std::string text to the one being rendered
         */
        void AppendString(std::string& text);

        virtual void Render();

    protected:

    private:
        /**
         * \brief The background image for the box, if any
         */
        Image m_bg_image;
        bool m_has_bg;

        /**
         * \brief The texture used to render the text on screen
         */
        std::unique_ptr<Texture> m_text_texture;

        /**
         * \see Transform
         */
        Transform m_transform;

        /**
         * \brief content of the box
         */
        std::string m_text;

        /**
         * \brief The font used to render the text
         */
        Font* m_font;

        /**
         * \brief Mutex controlling the access to the box, to avoid rendering conflicts
         */
        std::mutex m_mutex;

        /**
         * \brief Raw pointer to main resource manager
         */
        ResourceManager* m_resource_manager_ptr;
};

#endif // TEXTBOX_HPP
