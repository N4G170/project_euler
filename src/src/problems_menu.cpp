#include "problems_menu.hpp"
#include "message_writer.hpp"
#include "eulerproblems.hpp"

#include <fstream>
#include <iostream>
#include <utility>
#include <functional>
#include <future>
#include <thread>
#include <vector>

#include "sdl_gui_constants.hpp"
#include "sdl_gui_scroll_box.hpp"

ProblemsMenu::ProblemsMenu(sdl_gui::GuiManager* gui_manager, StateMachine* state_machine, const std::string& name, MainFlags* main_flags, std::mutex* render_mutex):
    StateInterface{state_machine, name, main_flags}, m_render_mutex{render_mutex}
{
    auto config{state_machine->SdlConfig()};

    auto bg{gui_manager->CreateElement<sdl_gui::Image>({0,0}, {static_cast<float>(config.window_w), static_cast<float>(config.window_h)} )};
    bg->ChangeTexture("data/ui/bg.png");
    bg->RenderIndex(10);//in the back

    auto input_container{gui_manager->CreateElement<sdl_gui::GuiElement>( {100, 50}, {0,0} )};

    m_results_box = gui_manager->CreateElement<sdl_gui::ScrollBox>({400,50}, {300,300});

    float input_x{0}, input_y{0};

    //<f> Input label
    m_input_label = gui_manager->CreateElement<sdl_gui::Label>({50,50}, {0,0});
    m_input_label->FontSize(25);
    m_number = "000";
    m_input_label->Text(m_number, sdl_gui::Colour::White);

    m_input_label->Parent(input_container);
    m_input_label->LocalPosition({ 170/2.f - m_input_label->Size().w/2.f, input_y });
    m_input_label->RenderIndex(-1);

    //bg for Label
    auto bg_size{m_input_label->Size()};
    bg_size.w += 10;
    bg_size.h += 8;

    auto label_bg{gui_manager->CreateElement<sdl_gui::Image>({0,0}, bg_size)};
    label_bg->ColourModulation({12,34,56,255});
    label_bg->Parent(input_container);
    label_bg->LocalPosition({ 170/2.f - m_input_label->Size().w/2.f - 5, input_y - 4 });


    input_y = m_input_label->Size().h + 5;

    //reset number
    m_number = "";
    m_input_label->Text(m_number, sdl_gui::Colour::White);
    //</f> /Input label

    //<f> Buttons
    //<f> numbers

    std::vector<sdl_gui::Button*> number_buttons;
    for(auto i{0}; i<10; ++i)
    {
        auto button{ gui_manager->CreateElement<sdl_gui::Button>({0,0}, {50,50}) };

        button->Parent(input_container);
        button->LocalPosition({0, 50.f * i});

        button->CreateLabel(std::to_string(i), sdl_gui::c_default_font_path, 20, {255,255,255,255}, {0,0});
        button->CentreLabel();

        button->TransitionColourPtr()->SetStateColour({64,64,64,128}, {64,64,64,255}, {96,96,96,255}, {128,128,128,255});

        button->MouseInteractionPtr()->MouseButtonCallback(SDL_BUTTON_LEFT, sdl_gui::InputKeyCallbackType::CLICK,
            std::bind(&ProblemsMenu::AddNumber, this, i ) );

        number_buttons.push_back(button);
    }

    //rearrange number buttons
    number_buttons[1]->LocalPosition({input_x, input_y});
    input_x+=60;
    number_buttons[2]->LocalPosition({input_x, input_y});
    input_x+=60;
    number_buttons[3]->LocalPosition({input_x, input_y});

    input_x = 0; input_y += 60;
    number_buttons[4]->LocalPosition({input_x, input_y});
    input_x+=60;
    number_buttons[5]->LocalPosition({input_x, input_y});
    input_x+=60;
    number_buttons[6]->LocalPosition({input_x, input_y});

    input_x = 0; input_y += 60;
    number_buttons[7]->LocalPosition({input_x, input_y});
    input_x+=60;
    number_buttons[8]->LocalPosition({input_x, input_y});
    input_x+=60;
    number_buttons[9]->LocalPosition({input_x, input_y});

    input_x = 60; input_y +=60;
    number_buttons[0]->LocalPosition({input_x, input_y});
    //</f> /numbers

    //<f> Function buttons
    input_x = 0;
    auto clear{gui_manager->CreateElement<sdl_gui::Button>({0,0}, {50,50})};
    clear->Parent(input_container);
    clear->LocalPosition({input_x, input_y});
    clear->TransitionColourPtr()->SetStateColour({64,64,64,128}, {64,64,64,255}, {96,96,96,255}, {128,128,128,255});
    clear->CreateLabel("Clear", sdl_gui::c_default_font_path, 15, {255,255,255,255}, {0,0});
    clear->CentreLabel();
    clear->MouseInteractionPtr()->MouseButtonCallback(SDL_BUTTON_LEFT, sdl_gui::InputKeyCallbackType::CLICK,
        std::bind(&ProblemsMenu::Clear, this ) );

    input_x = 120;
    auto ok{gui_manager->CreateElement<sdl_gui::Button>({0,0}, {50,50})};
    ok->Parent(input_container);
    ok->LocalPosition({input_x, input_y});
    ok->TransitionColourPtr()->SetStateColour({64,64,64,128}, {64,64,64,255}, {96,96,96,255}, {128,128,128,255});
    ok->CreateLabel("OK", sdl_gui::c_default_font_path, 15, {255,255,255,255}, {0,0});
    ok->CentreLabel();
    ok->MouseInteractionPtr()->MouseButtonCallback(SDL_BUTTON_LEFT, sdl_gui::InputKeyCallbackType::CLICK,
        std::bind(&ProblemsMenu::RequestProblem, this ) );
    //</f> /Function buttons

    //</f> /Buttons

    //<f> Number of Problems
    auto problems_label{gui_manager->CreateElement<sdl_gui::Label>({0,0}, {0,0})};
    problems_label->Text("Available Problems: 1-25, 27, 29, 30, 34-36, 40, 42, 48, 49, 52, 67, 71-73, 80, 81, 83, 92, 94");
    problems_label->Parent(input_container);
    problems_label->LocalPosition({-25, input_y + 100});
    //</f> /Number of Problems
}


ProblemsMenu::~ProblemsMenu()
{

}

void ProblemsMenu::Input(const SDL_Event& event)
{
    if( event.type == SDL_QUIT)
    {
        return;
    }
    else if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE: m_main_flags_ptr->quit = true; break;

            //<f> Numpad input
            case SDLK_0: case SDLK_KP_0: AddNumber(0); break;
            case SDLK_1: case SDLK_KP_1: AddNumber(1); break;
            case SDLK_2: case SDLK_KP_2: AddNumber(2); break;
            case SDLK_3: case SDLK_KP_3: AddNumber(3); break;
            case SDLK_4: case SDLK_KP_4: AddNumber(4); break;
            case SDLK_5: case SDLK_KP_5: AddNumber(5); break;
            case SDLK_6: case SDLK_KP_6: AddNumber(6); break;
            case SDLK_7: case SDLK_KP_7: AddNumber(7); break;
            case SDLK_8: case SDLK_KP_8: AddNumber(8); break;
            case SDLK_9: case SDLK_KP_9: AddNumber(9); break;
            //</f> /Numpad input

            //<f> Functions
            case SDLK_RETURN: case SDLK_KP_ENTER: RequestProblem(); break;
            case SDLK_BACKSPACE: case SDLK_DELETE: Clear(); break;
            //</f> /Functions
        }
    }
}

void ProblemsMenu::Logic(float delta_time)
{
    //checks if a running problem finished processing and prints its result
    for(auto& problem : m_problems_future)
    {
        //the auto var will be a std::pair, being the Key the first var and its value the second var
        //the second itself is a std::pair, that holds a bool(first) that tells if the problem is running
        //and the second holds the problem future
        if(problem.second.first && problem.second.second.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
        // if(problem.second.first && problem.second.second.valid())
        {
            problem.second.first = false;
            m_results_box->CreateItem(problem.second.second.get());
        }

    }
}

void ProblemsMenu::Render(float delta_time){}

void ProblemsMenu::Enter(){}
void ProblemsMenu::Exit(){}

void ProblemsMenu::AddNumber(int n)
{
    if(m_number.length() >= 3)
        return;

    m_number.append(std::to_string(n));
    m_input_label->Text(m_number, sdl_gui::Colour::White);
}

void ProblemsMenu::Clear()
{
    m_number.clear();
    m_input_label->Text(m_number, sdl_gui::Colour::White);
}

void ProblemsMenu::RequestProblem()
{
    if(m_number.empty())
    {
        m_results_box->CreateItem("Insert a problem number");
        return;
    }

    auto requested_problem{std::stoul(m_number)};

    //check if we are running it
    if(m_problems_future[requested_problem].first)//future exists and is running
    {
        m_results_box->CreateItem("Problem "+m_number+" already running");
        return;
    }

    m_results_box->CreateItem("Requested problem "+m_number);

    switch(requested_problem)
    {
        case 1: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem001); break;
        case 2: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem002); break;
        case 3: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem003); break;
        case 4: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem004); break;
        case 5: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem005); break;
        case 6: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem006); break;
        case 7: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem007); break;
        case 8: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem008); break;
        case 9: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem009); break;
        case 10: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem010); break;

        case 11: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem011); break;
        case 12: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem012); break;
        case 13: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem013); break;
        case 14: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem014); break;
        case 15: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem015); break;
        case 16: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem016); break;
        case 17: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem017); break;
        case 18: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem018); break;
        case 19: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem019); break;
        case 20: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem020); break;

        case 21: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem021); break;
        case 22: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem022); break;
        case 23: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem023); break;
        case 24: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem024); break;
        case 25: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem025); break;

        //case 26: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem026); break;
        case 27: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem027); break;
        //case 28: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem028); break;
        case 29: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem029); break;
        case 30: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem030); break;

        case 34: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem034); break;
        case 35: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem035); break;
        case 36: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem036); break;
        case 40: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem040); break;

        case 42: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem042); break;

        //case 47: if(!m_problems_future[requested_problem].first){ m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem047); } break;
        case 48: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem048); break;
        case 49: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem049); break;

        case 52: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem052); break;
        // case 54: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem054); break;

        //case 61: if(!m_problems_future[requested_problem].first){ m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem061); } break;
        case 67: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem067); break;

        case 71: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem071); break;
        case 72: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem072); break;
        case 73: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem073); break;
        //case 74: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem074); break;

        case 80: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem080); break;
        case 81: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem081); break;
        //case 82: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem082); break;
        case 83: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem083); break;

        case 92: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem092); break;
        case 94: m_problems_future[requested_problem].first = true; m_problems_future[requested_problem].second = std::async(std::launch::async, &Problem094); break;

        default: m_results_box->CreateItem("Problem "+m_number+" does not exist"); break;
    }

    Clear();//clear input label
}
