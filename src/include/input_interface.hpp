#ifndef INPUTINTERFACE_HPP
#define INPUTINTERFACE_HPP

#include <SDL2/SDL.h>
#include <functional>
#include <string>

/**
 * \brief Basic Interface to add behaviours to elements
 */
class InputInterface
{
    public:
        virtual ~InputInterface(){};

        //this pure virtual might need to be moved to a better interface
        virtual void Input(const SDL_Event& event) = 0;

        /**
         * \brief std::function to define OnClick() behaviour
         */
        std::function<void()> OnClickVoid;

        /**
         * \brief std::function to define OnClick(std::string) behaviour
         */
        std::function<void(std::string)> OnClick;
};
#endif // INPUTINTERFACE_HPP
