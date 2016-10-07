#pragma once

#include "common.h"
#include "libxml/parser.h"
#include <string>

//Non class-based programming

xmlDocPtr parseXML(const std::string& filename);

inline void bypassText(xmlNodePtr& node) {
	while (node && node->type == XML_TEXT_NODE) node = node->next;
}
inline void switchNextNode(xmlNodePtr& node) {
	do node = node->next; while (node && node->type == XML_TEXT_NODE);
}

std::string getNodeAttribute(xmlNodePtr node, const std::string& attribName);
std::string getNodeContent(xmlNodePtr node);

inline int childCount(xmlNodePtr node) {
	return int(xmlChildElementCount(node));
}

inline int childCountName(xmlNodePtr node) {

}

/*bool checkAttributeExists(xmlNodePtr node, const std::string& attribName) {
	return xmlGetProp(node, (const xmlChar *)attribName.c_str()) != nullptr;
}*/

inline bool checkName(xmlNodePtr node, const std::string& name) {
	return !xmlStrcmp(node->name, (const xmlChar *)name.c_str());
}

inline int asInt(xmlNodePtr node, const std::string& attribName, int noValue = 0) {
	const std::string& attribute = getNodeAttribute(node, attribName);
	return (attribute.empty()) ? noValue : std::stoi(attribute);
}

inline std::string asString(xmlNodePtr node, const std::string& attribName) {
	return getNodeAttribute(node, attribName);
}

inline float asFloat(xmlNodePtr node, const std::string& attribName, float noValue = 0.0f) {
	const std::string& attribute = getNodeAttribute(node, attribName);
	return (attribute.empty()) ? noValue : std::stof(attribute);
}

inline bool asBool(xmlNodePtr node, const std::string& attribName, bool noValue = false) {
	const std::string& attribute = getNodeAttribute(node, attribName);
	return (attribute.empty()) ? noValue : (attribute == "true");
}

//std::string asString(AXAttribute* attribute);
//int asInt(AXAttribute* attribute);
//bool asBool(AXAttribute* attribute);
//PathType asPathType(AXAttribute* attribute);

//AXElement* readDocument(const char* filename, AXParseContext* parseContext, AXElementClass* clazz);
//AXElementClass* readClass(const char* filename, AXClassContext* classContext);
//int countElements(AXElement* root);
//int countElementsID(AXElement* root, int targetID);

//AXElement* InitializeXMLParser (const char* shemaName, const char* sourceName, AXClassContext* classContext, AXParseContext* context);
//void freeXMLParser (AXClassContext* classContext, AXParseContext* context);

int getFileSize(FILE* f);
//void fileToCharBuffer(const char* filename, char* buffer);

