#include "state_machine.hpp"
#include "problems_menu.hpp"
#include "splash_screen.hpp"

StateMachine::StateMachine(SDL_Renderer* renderer, sdl_gui::ResourceManager* resource_manager, MainFlags* main_flags, SDLInitConfig sdl_config): m_renderer_ptr{renderer},
    m_gui_manager{renderer, resource_manager}, m_resource_manager_ptr{resource_manager}, m_main_flags_ptr{main_flags}, m_sdl_config{sdl_config}
{

}

StateMachine::~StateMachine()
{
    m_current_state.reset(nullptr);
    m_previous_state.reset(nullptr);

    m_resource_manager_ptr = nullptr;
    m_renderer_ptr = nullptr;
    m_main_flags_ptr = nullptr;
    //tyhe gui manager will clear everything on destroy
}

/**
 * \brief Sets next state
 * \details Receives a string with the name for the next state. (Might change it to an enumerate)
 */
void StateMachine::ChangeState(const std::string& state)
{
    if(m_current_state)//store previous state
    {
        m_previous_state.reset(m_current_state.release());
        m_previous_state->Exit();
    }
    if(m_previous_state && m_previous_state->Name() == state)//revert to previous state
    {
        m_current_state.swap(m_previous_state);

        m_previous_state->Exit();
        m_current_state->Enter();
        return;
    }
    if(state == StateName::Splash)
    {
        m_current_state.reset(new SplashScreen(&m_gui_manager, this, StateName::Splash, m_main_flags_ptr));
        m_current_state->Enter();
    }
    else if(state == StateName::Problems)
    {
        m_current_state.reset(new ProblemsMenu(&m_gui_manager, this, StateName::Problems, m_main_flags_ptr, &m_render_mutex));
        m_current_state->Enter();
    }
}

/**
 * \brief Calls Input for current state
 */
void StateMachine::Input(const SDL_Event& event)
{
    if(m_current_state)
        m_current_state->Input(event);

    m_gui_manager.Input(event);
}

/**
 * \brief Calls Logic for current state
 */
void StateMachine::Logic(float delta_time)
{
    if(m_current_state)
        m_current_state->Logic(delta_time);

    m_gui_manager.Logic(delta_time);
}

/**
 * \brief Calls Render for current state
 */
void StateMachine::Render(float delta_time)
{
    std::lock_guard<std::mutex> lock(m_render_mutex);

    if(m_current_state)
        m_current_state->Render(delta_time);

    m_gui_manager.Render(delta_time);
}
