#ifndef SPLASHSCREEN_HPP
#define SPLASHSCREEN_HPP

#include "state_interface.hpp"
#include "sdl_gui_manager.hpp"
#include "sdl_gui_image.hpp"
#include "sdl_gui_label.hpp"

/**
 * \brief MainMenu state (currently the initial state used by the state machine)
 */
class SplashScreen : public StateInterface
{
    public:
        SplashScreen(sdl_gui::GuiManager*, StateMachine*, const std::string&, MainFlags*);
        virtual ~SplashScreen();

        //BasicInterface
        void Input(const SDL_Event&) override;
        //BasicInterface
        void Logic(float delta_time) override;
        //BasicInterface
        void Render(float delta_time) override;

        void Enter() override;

        void Exit() override;

    private:
        sdl_gui::Image* m_image;
        sdl_gui::Label* m_blink_text;

        float m_timer;
};

#endif // SPLASHSCREEN_HPP
