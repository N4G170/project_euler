#include "textbox.hpp"
#include <iostream>
#include <algorithm>

#include "utils.hpp"

TextBox::TextBox(ResourceManager* resource_manager, const Json::Value& config):m_resource_manager_ptr{resource_manager}
{
    m_transform.rect.x = config["x"].asInt();
    m_transform.rect.y = config["y"].asInt();
    m_transform.rect.w = config["w"].asInt();
    m_transform.rect.h = config["h"].asInt();

    Json::Value bg = config["bg"];
    m_has_bg = bg["has_bg"].asBool();

    if(m_has_bg)
        m_bg_image = Image(resource_manager, bg["bg_name"].asString(), Defaults::FullImageRect, m_transform.rect, bg["z_index"].asInt());

    m_text_texture.reset(new Texture(m_resource_manager_ptr->GetRendererPtr(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, m_transform.rect.w, m_transform.rect.h) );

    Text(config["text"].asString());
}

TextBox::~TextBox()
{
    m_font = nullptr;
}

void TextBox::Render()
{
    m_mutex.lock();

    if(m_has_bg)
    {
        m_bg_image.Render();//TODO: config src and dst
    }
    if(m_text_texture)
    {
        m_text_texture->Render(m_transform.rect, false);
    }

    m_mutex.unlock();
}

void TextBox::Text(const std::string& text )
{
    m_mutex.lock();

    m_text = text;

    //create texture
    m_text_texture.reset();
    m_mutex.unlock();
}

void TextBox::AppendString(std::string& text )
{
    m_mutex.lock();
    m_text.append(text);
    m_mutex.unlock();
}
