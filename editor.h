#ifndef EDITOR_H_INCLUDED
#define EDITOR_H_INCLUDED

#include "common.h"
#include "vector.h"
#include "graphics/renderers/renderEditor.h"

class Editor
{
    public:
        Editor(Level** level);

        MarioMode update(KeyStates* keystates);

    private:
        Level** m_currentLevel;

        Object* m_moveHandle;
        Object* m_creaHandle;
        bool m_viewHandle;
        Vect2i m_moveEntityPos;
        Vect2i m_creatingPos;
        Vect2i m_moveViewPos;

        int m_selectedEntity;

        friend Graphics::RenderEditor;
};

#endif // EDITOR_H_INCLUDED
