#include "menu.h"
#include "ui/button.h"
#include "input.h"
#include "level.h"
#include "sound.h"
#include "filetool.h"
#include <SDL.h>

Menu::Menu(Level** level)
{
    readMenuFile();
    m_mode = MAIN_MENU;
    resetMode(MAIN_MENU);
    resetMode(LEVEL_SELECTION);
    m_currentLevel = level;
    soundStack->changeMusic(Musics::MENU);
}

void Menu::readMenuFile()
{
	xmlDocPtr menuDoc = parseXML("menu/menu.xml");
	xmlNodePtr menuModeN = xmlDocGetRootElement(menuDoc)->xmlChildrenNode;
	bypassText(menuModeN);

	unsigned int currentModeID;
	unsigned int currentButtonID;

	while (menuModeN)
	{
		xmlNodePtr buttonN = menuModeN->children;
		bypassText(buttonN);

		currentModeID = asInt(menuModeN, "id");
		if (m_buttons.size() <= currentModeID) m_buttons.resize(currentModeID + 1);

		while (buttonN)
		{
			currentButtonID = asInt(buttonN, "id");
			if (m_buttons[currentModeID].size() <= currentButtonID) m_buttons[currentModeID].resize(currentButtonID + 1);
			if (currentModeID == LEVEL_SELECTION)
			{
				if (m_levelNames.size() <= currentButtonID) m_levelNames.resize(currentButtonID + 1);
				m_levelNames[currentButtonID] = "levels/" + asString(buttonN, "levelName") + ".xml";
			}
			m_buttons[currentModeID][currentButtonID] = new Button(asInt(buttonN, "X"), asInt(buttonN, "Y"), asInt(buttonN, "texID"));

			switchNextNode(buttonN);
		}
		switchNextNode(menuModeN);
	}

	xmlFreeDoc(menuDoc);
}

MarioMode Menu::update(KeyStates* keystates)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    bool keyPress = (keystates->isDown() || keystates->isUp() || keystates->isSpace());
    if(!keyPress) m_keyPressed = false;
    if(keyPress && !m_keyPressed)      // Register user action once
    {
        m_keyPressed = true;

        m_buttons[m_mode][m_selection]->setState(Button::State::UNSELECTED);
        if(keystates->isDown() && (m_selection < m_buttons[m_mode].size()-1))
        {
            m_selection++;
            soundStack->addToStack(Sounds::MENU_CURSOR);
        }
        if(keystates->isUp() && (m_selection > 0))
        {
            m_selection--;
            soundStack->addToStack(Sounds::MENU_CURSOR);
        }
        m_buttons[m_mode][m_selection]->setState(Button::State::SELECTED);

        if(keystates->isSpace()) return selectButton();
    }
    else if(keystates->isMouseLeftDown())
    {
        if(m_buttons[m_mode][m_selection]->getRect().isInside(x,y)) return selectButton();
    }
    else if(x != m_oldMouseX || y != m_oldMouseY)
    {
        int insideButton = -1;
        for(unsigned int i = 0; i < m_buttons[m_mode].size(); i++)
        {
            if(m_buttons[m_mode][i] != NULL && m_buttons[m_mode][i]->getRect().isInside(x,y) && i != m_selection) {insideButton = i; break;}
        }
        if(insideButton != -1)
        {
            m_buttons[m_mode][m_selection]->setState(Button::State::UNSELECTED);
            m_selection = insideButton;
            soundStack->addToStack(Sounds::MENU_CURSOR);
            m_buttons[m_mode][m_selection]->setState(Button::State::SELECTED);
        }
        m_oldMouseX = x; m_oldMouseY = y;
    }

    return MODE_MENU;
}

MarioMode Menu::selectButton()
{
    soundStack->addToStack(Sounds::MENU_SELECTION);
    switch (m_mode)
    {
        case MAIN_MENU:
            switch (m_selection)
            {
                case 0:
                    m_mode = LEVEL_SELECTION;
                    m_editing = false;
                    resetMode(MAIN_MENU);
                    break;
                case 1:
                    return MODE_QUIT;
                    break;
            }
            break;
        case LEVEL_SELECTION:
            delete (*m_currentLevel);
            (*m_currentLevel) = new Level(m_levelNames[m_selection]);
            m_mode = MAIN_MENU;
            resetMode(LEVEL_SELECTION);
            return m_editing ? MODE_EDITOR : MODE_LEVEL;
            break;
    }
    return MODE_MENU;
}

void Menu::resetMode(MenuMode mode)
{
    m_selection = 0;
    m_buttons[mode][0]->setState(Button::State::SELECTED);
    for(std::vector<Button*>::iterator it = m_buttons[m_mode].begin()+1; it != m_buttons[m_mode].end(); ++it)
    {
        if((*it) != NULL) (*it)->setState(Button::State::UNSELECTED);
    }
}

Menu::~Menu()
{
    for(std::vector< std::vector<Button*> >::iterator it = m_buttons.begin(); it != m_buttons.end(); ++it)
    {
        for (std::vector<Button*>::iterator it2 = (*it).begin(); it2 != (*it).end(); ++it2)
        {
            delete (*it2);
        }
    }
}
