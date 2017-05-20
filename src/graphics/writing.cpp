#include "writing.h"
#include "texture.h"

using namespace Graphics;

Write::Write(SDL_Renderer* renderer)
{
    if(TTF_Init()) {std::cout << "Initialized TTF\n";}

    m_defaultColor = COLOR_BLACK;
    m_defaultFont = new Font("txt.TTF", 28, m_defaultColor);
    m_renderer = renderer;
}

Write::~Write()
{
    delete m_defaultFont;
    TTF_Quit();
}

void Write::write(std::string text, Texture* drawOn, Font* font)
{
    if (font == NULL)
    {
        font = m_defaultFont;
    }
    SDL_Surface* temp = TTF_RenderText_Blended(font->getFont(), text.c_str(), font->getColor().getSDLColor());
    drawOn->setfromSDLSurface(temp);
    SDL_FreeSurface(temp);
}

Font::Font(std::string name, int size, Color color)
{
    m_font = TTF_OpenFont(name.c_str(), size);
    m_color = color;
}

Font::~Font()
{
    TTF_CloseFont(m_font);
}
