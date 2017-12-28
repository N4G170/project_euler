#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <set>
#include <map>
#include <thread>
#include <mutex>
#include <future>
#include <utility>
#include <string>

#include "state_interface.hpp"
#include "sdl_gui_image.hpp"
#include "sdl_gui_button.hpp"
#include "sdl_gui_manager.hpp"
#include "sdl_gui_scroll_box.hpp"
#include "sdl_gui_label.hpp"

#include <mutex>
/**
 * \brief Problems menu state
 */
class ProblemsMenu : public StateInterface
{
    public:
        ProblemsMenu(sdl_gui::GuiManager*, StateMachine*, const std::string&, MainFlags*, std::mutex*);
        virtual ~ProblemsMenu();

        //BasicInterface
        void Input(const SDL_Event&) override;
        //BasicInterface
        void Logic(float delta_time) override;
        //BasicInterface
        void Render(float delta_time) override;

        void Enter() override;

        void Exit() override;

    private:

        /**
         * \brief Stores the futures of running problems
         */
        std::map< int, std::pair<bool, std::future<std::string>> > m_problems_future;

        sdl_gui::Label* m_input_label;
        sdl_gui::ScrollBox* m_results_box;

        std::mutex* m_render_mutex;

        std::string m_number;
        void AddNumber(int n);
        void Clear();
        /**
         * \brief Reads the input box and tries to start the corresponding problem
         */
        void RequestProblem();
};

#endif // MAINMENU_HPP
