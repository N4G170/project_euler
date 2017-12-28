#include "image.hpp"

Image::Image()
{
    m_render_object = true;
    m_texture_ptr = nullptr;
    m_resource_manager_ptr = nullptr;
}

Image::Image(ResourceManager* resource_manager, const Json::Value& data): m_resource_manager_ptr{resource_manager}
{
    m_texture_ptr = m_resource_manager_ptr->GetTexture(data["texture"].asString());

    Json::Value rect = data["rect"];
    m_render_object = true;

    if(rect["src"].asBool())//a source rect was defined (area of the texture to be rendered)
    {
        m_source_rect.x = rect["src_x"].asInt();
        m_source_rect.y = rect["src_y"].asInt();

        if(rect["src_w"].asInt() > -1)
            m_source_rect.w = rect["src_w"].asInt();
        else
            m_source_rect.w = m_texture_ptr->Size().w;
        if(rect["src_h"].asInt() > -1)
            m_source_rect.h = rect["src_h"].asInt();
        else
            m_source_rect.h = m_texture_ptr->Size().h;
    }
    else
    {
        m_source_rect = m_texture_ptr->Size();
    }

    rect = data["rect"];

    if(rect["dst"].asBool())//a destination rect was defined (area of the screen to render the texture on)
    {
        m_destination_rect.x = rect["dst_x"].asInt();
        m_destination_rect.y = rect["dst_y"].asInt();

        if(rect["dst_w"].asInt() > -1)
            m_destination_rect.w = rect["dst_w"].asInt();
        else
            m_destination_rect.w = m_texture_ptr->Size().w;
        if(rect["dst_h"].asInt() > -1)
            m_destination_rect.h = rect["dst_h"].asInt();
        else
            m_destination_rect.h = m_texture_ptr->Size().h;
    }
    else
    {
        m_destination_rect = m_texture_ptr->Size();
    }

    m_z_index = data["z_index"].asInt();
}

Image::Image(ResourceManager* resource_manager, const std::string& texture_name, const SDL_Rect& src_rect, const SDL_Rect& dst_rect, const int& z_index):
    m_resource_manager_ptr{resource_manager}
{
    m_texture_ptr = m_resource_manager_ptr->GetTexture(texture_name);

    if(src_rect.w < 0 || src_rect.h < 0)//use entire image
        m_source_rect = m_texture_ptr->Size();
    else
        m_source_rect = src_rect;

    if(dst_rect.w < 0 || dst_rect.h < 0)//use entire image
        m_destination_rect = m_texture_ptr->Size();
    else
        m_source_rect = dst_rect;

    m_z_index = z_index;
}

Image::~Image()
{
    m_texture_ptr = nullptr;
    m_resource_manager_ptr = nullptr;
}

void Image::Render()
{
    if(m_texture_ptr && m_render_object)
    {
        m_texture_ptr->Render(m_source_rect, m_destination_rect);
    }
}
