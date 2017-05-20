#include "dialog.h"
#include "../filetool.h"
#include "../graphics/renderDatas.h"

Dialog* dialog;

Dialog::Dialog(std::string name)
{
	xmlDocPtr dialogDoc = parseXML("dialogs/" + name + ".xml");
	xmlNodePtr dialogN = xmlDocGetRootElement(dialogDoc);
	bypassText(dialogN);

	m_text = getNodeContent(dialogN->children);
	m_texID = asInt(dialogN, "texID");
	m_timer.setDelay(asInt(dialogN, "drawingTime"));
	m_timer.start();

	xmlFreeDoc(dialogDoc);
}

void Dialog::update()
{
    if(!m_timer.isRunning()) delete this;
}

Dialog::~Dialog()
{
    dialog = NULL;
}
