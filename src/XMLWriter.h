#ifndef XMLWRAPER_H_INCLUDED
#define XMLWRAPER_H_INCLUDED

#include "common.h"

#include <fstream>

class XMLWriter
{
    public:
        XMLWriter();
        ~XMLWriter();

        void writeStart(Uint16 tIndex);
        void writeCoords(int x, int y);
        void writeSize(int w, int h);
        void writeEnd();

        void writePlayer(int x, int y, std::string name, int keyset);
        void writeGoomba(int x, int y);
        void writeKoopa(int x, int y);
        void writeMushroom(int x, int y, int itemType);
        void writeDecor(int x, int y, int w, int h, int texID, int layer);
        void writeBrick(int x, int y);
        void writeGround(int x, int y, int w, int h, int texID);
        void writeDialogTrigger(int x, int y, int w, int h, std::string dialogFile);
        void writeHandPaternTrigger(int x, int y, int w, int h, std::string handPaternFile);

    private:
        std::basic_fstream<char> m_file;

};

#endif // XMLWRAPER_H_INCLUDED
