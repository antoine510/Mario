#ifndef WRITING_H_INCLUDED
#define WRITING_H_INCLUDED

#include "../common.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "color.h"

namespace Graphics{
class Font
{
    public:
        Font(std::string name, int size, Color color);
        ~Font();

        inline void setColor(Color color) {m_color = color;}
        inline TTF_Font* getFont() const {return m_font;}
        inline Color getColor() const {return m_color;}

    private:
        TTF_Font* m_font;
        Color m_color;
};

class Write
{
    public:
        Write(SDL_Renderer* renderer);
        ~Write();
        void write(std::string text, Texture* drawOn, Font* font = NULL);

    private:
        Font* m_defaultFont;
        Color m_defaultColor;
        SDL_Renderer* m_renderer;
};
}

#endif // WRITING_H_INCLUDED
