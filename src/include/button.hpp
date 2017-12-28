#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SDL2/SDL.h>
#include <memory>

#include "structs.hpp"
#include "json.h"
#include "image.hpp"
#include "input_interface.hpp"
#include <functional>

/**
 * \brief Class to display a generic button
 * \details Creates and displays a button and defines its behaviour
 */
class Button : public RenderInterface, public InputInterface
{
    public:
        /** Default destructor */
        virtual ~Button();

        /** Basic constructor */
        Button();

        /**
         * \brief Implement Render from object
         */
        virtual void Render();

        /**
         * \brief Implements Input from InputInterface
         */
        virtual void Input(const SDL_Event& event);

    protected:
        /**
         * \brief Height of the sprite cell to be used on different states, like mouse hover
         */
        unsigned int m_section_height;
        /**
         * \brief Width of the sprite cell, to be used on different states, like mouse hover
         */
        unsigned int m_section_width;

        /**
         * \brief Flag to mark if the mouse is over the element or not.
         */
        bool m_mouse_hover;

        /**
         * \brief std::string with the text of the button
         */
        std::string m_value;

        /**
         * \brief Text element that renders the button text
         */
        //Text m_text;
};

#endif // BUTTON_HPP
