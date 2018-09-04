/*
* base interface of docment
* def interface£¬but not set pure virture, keep pod
*/
#pragma once
#include "Common.h"
#include "Utils.h"

NS_COLLADA_BEGIN

class DocBase {
	void initFromDoc(const CHAR_XML_NODE& doc) {};
};

class InitFrom:DocBase {
	std::string m_str;

public:
	void initFromDoc(const CHAR_XML_NODE& doc) { m_str = doc.value(); };
};

NS_COLLADA_END