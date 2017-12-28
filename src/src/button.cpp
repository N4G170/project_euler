#include "button.hpp"
#include <iostream>
#include <typeinfo>

Button::Button()
{
    // m_section_height = m_texture->GetHeight() / 3;
    // m_section_width = m_texture->GetWidth();
    //
    // m_value = object_json["value"].asString();
    //
    // m_transform.m_rect.w = (int)m_section_height;
    // m_transform.m_rect.h = (int)m_section_width;
    //
    // m_text.Set( object_json, main_pointers, &m_transform, false);
    //
    // m_mouse_hover = false;
}

Button::~Button()
{

}

/**
 * \brief Implement Render from object
 */
void Button::Render()
{
    // if(m_texture)
    // {
    //     SDL_Rect sectionQuad;
    //     if(m_mouse_hover)
    //         sectionQuad = { 0, (int)(m_section_height), (int)m_section_width, (int)m_section_height };
    //     else
    //         sectionQuad = { 0, 0, (int)m_section_width, (int)m_section_height };
    //
    //     //Set rendering space and render to screen
    //     SDL_Rect renderQuad = { m_transform.m_rect.x, m_transform.m_rect.y, (int)m_section_width, (int)m_section_height };//texture position
    //     SDL_RenderCopy( screen_renderer.get(), m_texture->GetSDL_TexturePtr(), &sectionQuad, &renderQuad );
    // }
    //
    // m_text.Render(screen_renderer);
}

/**
 * \brief Implements Input from InputInterface
 */
void Button::Input(const SDL_Event& event)
{
    //mouse move event
    // if( event.type == SDL_MOUSEMOTION )
    // {
    //     int x,y;
    //     //Get mouse position int x, y;
    //     SDL_GetMouseState( &x, &y );
    //
    //     //Mouse hover
    //     if( (y > m_transform.m_rect.y && y < (int)(m_transform.m_rect.y + m_section_height)) && (x > m_transform.m_rect.x && x < (int)(m_transform.m_rect.x + m_section_width)))
    //         m_mouse_hover = true;
    //     else
    //         m_mouse_hover = false;
    //
    // }
    // if( event.type == SDL_MOUSEBUTTONUP && m_mouse_hover)//button wa clicked
    // {
    //     if(OnClick)//has "delegate"?
    //     {
    //         OnClick( m_value );
    //     }
    //     if(OnClickVoid)//has "delegate"?
    //     {
    //         OnClickVoid();
    //     }
    //
    // }
}
