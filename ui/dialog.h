#ifndef DIALOG_H_INCLUDED
#define DIALOG_H_INCLUDED

#include "../common.h"

#include "../timer.h"
#include "../rectangle.h"
#include "../graphics/renderers/renderDialog.h"

class Dialog
{
    public:
        Dialog(std::string name);

        void update();

        inline int getTexID() const {return m_texID;}

        ~Dialog();
    private:
        std::string m_text;
        Timer m_timer;

        int m_texID;

        friend void Graphics::RenderDialog::render();
};

extern Dialog* dialog;

#endif // DIALOG_H_INCLUDED
