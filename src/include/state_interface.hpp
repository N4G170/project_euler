#ifndef BASICINTERFACE_HPP
#define BASICINTERFACE_HPP
#include <memory>
#include "SDL.h"

#include "structs.hpp"
#include "state_machine.hpp"

class StateMachine;
struct MainFlags;

/**
 * \brief Basic Interface to be used by the main state machine
 */
class StateInterface
{
    public:
        StateInterface(StateMachine* state_machine, const std::string& state_name, MainFlags* main_flags):m_state_machine_ptr{state_machine}, m_main_flags_ptr{main_flags},
        m_state_name{state_name} {};

        virtual ~StateInterface(){ m_state_machine_ptr = nullptr; m_main_flags_ptr = nullptr; };

        /**
         * \brief Precess SDL user input
         */
        virtual void Input(const SDL_Event&) = 0;

        /**
         * \brief Process any logic, runs after input
         */
        virtual void Logic(float delta_time) = 0;

        /**
         * \brief Render the state visual elements
         */
        virtual void Render(float delta_time) = 0;

        /**
         * \brief Not yet in use
         */
        virtual void Enter(){};

        /**
         * \brief Not yet in use
         */
        virtual void Exit(){};

        std::string Name() const { return m_state_name; }

    protected:
        StateMachine* m_state_machine_ptr;
        MainFlags* m_main_flags_ptr;
    private:
        std::string m_state_name;
};

#endif // BASICINTERFACE_HPP
