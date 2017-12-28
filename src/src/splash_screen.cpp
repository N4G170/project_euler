#include "splash_screen.hpp"
#include "message_writer.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>


SplashScreen::SplashScreen(sdl_gui::GuiManager* gui_manager, StateMachine* state_machine, const std::string& name, MainFlags* main_flags):
        StateInterface{state_machine, name, main_flags}, m_timer{0.f}
{
    auto config{state_machine->SdlConfig()};

    m_image = gui_manager->CreateElement<sdl_gui::Image>({0,0}, {static_cast<float>(config.window_w), static_cast<float>(config.window_h)});
    m_image->ChangeTexture("data/ui/splash_bg.png");
    m_image->RenderIndex(10);//in the back

    m_blink_text = gui_manager->CreateElement<sdl_gui::Label>({0,0}, {0,0});
    m_blink_text->Text("Press any key to start");

    m_blink_text->FontSize(40);
    m_blink_text->LocalPosition({ config.window_w/2.f - m_blink_text->Size().w / 2.f, 250 });
}


SplashScreen::~SplashScreen()
{

}

void SplashScreen::Input(const SDL_Event& event)
{
    //exit program if we click the X
    if( event.type == SDL_QUIT)
    {
        return;
    }
    else if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            // case SDLK_ESCAPE: m_main_flags_ptr->quit = true; break;//TMP
            default://any key press other than ESCAPE changes state
                m_state_machine_ptr->ChangeState(StateName::Problems);
            break;
        }
    }
}

void SplashScreen::Logic(float delta_time)
{
    m_timer += delta_time;

    if(m_timer >= 0.75f)
    {
        m_timer = 0;
        m_blink_text->Enabled(!m_blink_text->Enabled());
    }
}

void SplashScreen::Render(float delta_time) {}

void SplashScreen::Enter()
{
    if(m_image != nullptr)
        m_image->Enable();
    if(m_blink_text != nullptr)
        m_blink_text->Enable();
    m_timer = 0;
}

void SplashScreen::Exit()
{
    if(m_image != nullptr)
        m_image->Disable();
    if(m_blink_text != nullptr)
        m_blink_text->Disable();
}
