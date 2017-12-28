#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <memory>
#include <string>
#include "SDL.h"

#include "state_interface.hpp"
#include "constants.hpp"
#include "sdl_init.hpp"
#include "sdl_gui_manager.hpp"
#include "sdl_gui_resource_manager.hpp"

#include <mutex>

//class ResourceManager;
class StateInterface;

/**
 * \brief Basic state machine
 */
class StateMachine
{
    public:
        explicit StateMachine(SDL_Renderer*, sdl_gui::ResourceManager*, MainFlags*, SDLInitConfig);
        virtual ~StateMachine();

        /**
         * \brief Sets next state
         * \details Receives a string with the name for the next state. (Might change it to an enumerate)
         */
        void ChangeState(const std::string&);
        /**
         * \brief Returns the machine to its previous state (Not yet in use)
         */
        void ReturnToPreviousState();

        /**
         * \brief Calls Input for current state
         */
        void Input(const SDL_Event&);

        /**
         * \brief Calls Logic for current state
         */
        void Logic(float delta_time);

        /**
         * \brief Calls Render for current state. The renderer is passed with the resource manager
         */
        void Render(float delta_time);

        inline SDLInitConfig SdlConfig() const { return m_sdl_config; }

    protected:
    private:
        SDL_Renderer* m_renderer_ptr;

        sdl_gui::GuiManager m_gui_manager;
        sdl_gui::ResourceManager* m_resource_manager_ptr;

        std::unique_ptr<StateInterface> m_current_state;
        std::unique_ptr<StateInterface> m_previous_state;

        MainFlags* m_main_flags_ptr;
        SDLInitConfig m_sdl_config;
        std::mutex m_render_mutex;
};

#endif // STATEMACHINE_HPP
