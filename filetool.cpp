#include <cctype>
#include <cstdarg>
#include <cstdlib>
#include <cstdio>
#include "filetool.h"

xmlDocPtr parseXML(const std::string& filename) {
	xmlDocPtr doc = xmlParseFile(filename.c_str());

	if (doc == NULL) fprintf(stderr, "Error : XML file %s not parsed successfully\n", filename.c_str());

	return doc;
}

std::string getNodeAttribute(xmlNodePtr node, const std::string& attribName)
{
	xmlChar* attrib = xmlGetProp(node, (const xmlChar *)attribName.c_str());
	if (attrib != nullptr) {
		std::string str((char*)attrib);
		xmlFree((void*)attrib);
		return str;
	}
	else {
		return std::string();
	}
}

std::string getNodeContent(xmlNodePtr node)
{
	xmlChar* src = xmlNodeGetContent(node);
	if (src != nullptr) {
		std::string str((char*)src);
		xmlFree((void*)src);
		return str;
	}
	else {
		return std::string();
	}
}

/*std::string asString(AXAttribute* attribute)
{
    std::string resu;
    char* ptr;
    for (ptr = (char*)attribute->begin; ptr < attribute->limit; ptr++)
    {
        resu.push_back(*ptr);
    }
    return resu;
}*/

/*int asInt(AXAttribute* attribute)
{
    std::string resu;
    char* ptr;
    for (ptr = (char*)attribute->begin; ptr < attribute->limit; ptr++)
    {
        resu.push_back(*ptr);
    }
    return std::atoi(resu.c_str());
}*/

/*bool asBool(AXAttribute* attribute)
{
    return (*(char*)(attribute->begin) == 't');
}*/

/*PathType asPathType(AXAttribute* attribute)
{
    std::string t = asString(attribute);
    if(t == "linear") {return LINEAR;}
    if(t == "squared") {return SQUARED;}
    return LINEAR;
}*/

/*AXElement* readDocument(const char* filename, AXParseContext* parseContext, AXElementClass* clazz)
{
    char buffer[XML_MAX_FILE_SIZE];
    fileToCharBuffer(filename, buffer);

    return ax_parse(parseContext, buffer, clazz, 1);
}

AXElementClass* readClass(const char* filename, AXClassContext* classContext)
{
    char buffer[XML_MAX_FILE_SIZE];
    fileToCharBuffer(filename, buffer);

    return ax_classFromString(buffer, classContext);
}

int countElements(AXElement* root)
{
    int total = 0;
    while (root) {total++; root = root->nextSibling;}
    return total;
}

int countElementsID(AXElement* root, int targetID)
{
    int total = 0;
    while (root) {if(root->id == targetID) total++; root = root->nextSibling;}
    return total;
}*/

int getFileSize(FILE* f)
{
    int pos = ftell(f);
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    fseek(f, pos, SEEK_SET);

    return size ;
}

/*void fileToCharBuffer(const char* filename, char* buffer)
{
    FILE*    f;
    size_t  size;

    f = fopen(filename, "r");
    if(f == NULL)
    {
        std::cerr << "Error opening XML file " << filename;
    }
    size = fread(buffer, 1, XML_MAX_FILE_SIZE-1, f);
    buffer[size] = 0;
    fclose(f);
}*/

/*AXElement* InitializeXMLParser (const char* shemaName, const char* sourceName, AXClassContext* classContext, AXParseContext* context)
{
    ax_initialize((void*)malloc, (void*)free);

    if(ax_initializeClassParser(classContext) != 0) std::cerr << "Error initializing the AsmXML class parser" << std::endl;

    AXElementClass* rootClass = readClass(shemaName, classContext);

    if(ax_initializeParser(context, XML_CHUNK_SIZE) != 0) std::cerr << "Error initializing the AsmXML file parser" << std::endl;
    AXElement* temp = readDocument(sourceName, context, rootClass);
    if(temp == NULL) std::cerr << "Error " << classContext->errorCode << " reading XML file : " << sourceName;
    return temp;
}

void freeXMLParser (AXClassContext* classContext, AXParseContext* context)
{
    ax_releaseParser(context);
    ax_releaseClassParser(classContext);
}*/

