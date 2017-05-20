#include "XMLWriter.h"
#include "entities/entityTypes.h"

XMLWriter::XMLWriter()
{
    m_file.open("XMLoutput/level.xml", std::ios::out);
    m_file << "<?xml version=\"1.0\" ?>" << std::endl;
    m_file << "<Level name=\"First\">" << std::endl;
}

void XMLWriter::writeStart(Uint16 tIndex)
{
    switch (tIndex)
    {
        case TINDEX_PLAYER:
            m_file << " <Player ";
            break;
        case TINDEX_GOOMBA:
            m_file << " <Goomba ";
            break;
        case TINDEX_KOOPA:
            m_file << " <Koopa ";
            break;
        case TINDEX_MUSHROOM:
            m_file << " <Mushroom ";
            break;
        case TINDEX_DECOR:
            m_file << " <Decor ";
            break;
        case TINDEX_GROUND:
            m_file << " <Ground ";
            break;
        case TINDEX_BRICK:
            m_file << " <Brick ";
            break;
        case TINDEX_SWITCH:
            m_file << " <Switch ";
            break;
        case TINDEX_TRIGGER_HP:
            m_file << " <HandPaternTrigger ";
            break;
        case TINDEX_TRIGGER_DIALOG:
            m_file << " <DialogTrigger ";
            break;
        case TINDEX_TRIGGER_END:
            m_file << " <EndTrigger ";
            break;
    }
}

void XMLWriter::writeCoords(int x, int y)
{
    m_file << "X=\"" << x << "\" Y=\"" << y << "\" ";
}

void XMLWriter::writeSize(int w, int h)
{
    m_file << "W=\"" << w << "\" H=\"" << h << "\" ";
}

void XMLWriter::writeEnd()
{
    m_file << "/>";
}

void XMLWriter::writePlayer(int x, int y, std::string name, int keyset)
{
    m_file << " <Player X=\"" << x << "\" Y=\"" << y << "\" name=\"" << name << "\" keySet=\"" << keyset << "\" />" << std::endl;
}

void XMLWriter::writeGoomba(int x, int y)
{
    m_file << " <Goomba X=\"" << x << "\" Y=\"" << y << "\" />" << std::endl;
}

void XMLWriter::writeKoopa(int x, int y)
{
    m_file << " <Koopa X=\"" << x << "\" Y=\"" << y << "\" />" << std::endl;
}

void XMLWriter::writeMushroom(int x, int y, int itemType)
{
    m_file << " <Mushroom X=\"" << x << "\" Y=\"" << y << "\" itemType=\"" << itemType << "\" />" << std::endl;
}

void XMLWriter::writeDecor(int x, int y, int w, int h, int texID, int layer)
{
    m_file << " <Decor X=\"" << x << "\" Y=\"" << y << "\" W=\"" << w << "\" H=\"" << h << "\" texID=\"" << texID << "\" layer=\"" << layer <<  "\" />" << std::endl;
}

void XMLWriter::writeBrick(int x, int y)
{
    m_file << " <Brick X=\"" << x << "\" Y=\"" << y << "\" />" << std::endl;
}

void XMLWriter::writeGround(int x, int y, int w, int h, int texID)
{
    m_file << " <Ground X=\"" << x << "\" Y=\"" << y << "\" W=\"" << w << "\" H=\"" << h << "\" texID=\"" << texID << "\" />" << std::endl;
}

void XMLWriter::writeDialogTrigger(int x, int y, int w, int h, std::string dialogFile)
{
    m_file << " <DialogTrigger X=\"" << x << "\" Y=\"" << y << "\" W=\"" << w << "\" H=\"" << h << "\" dialogFile=\"" << dialogFile << "\" />" << std::endl;
}

void XMLWriter::writeHandPaternTrigger(int x, int y, int w, int h, std::string handPaternFile)
{
    m_file << " <HandPaternTrigger X=\"" << x << "\" Y=\"" << y << "\" W=\"" << w << "\" H=\"" << h << "\" handPaternFile=\"" << handPaternFile << "\" />" << std::endl;
}

XMLWriter::~XMLWriter()
{
    m_file << "</Level>";
    m_file.close();
}
