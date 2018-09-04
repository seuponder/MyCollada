/*
* reader about library_images tag
*/
#pragma once

#include "Common.h"
#include "Utils.h"
#include "DocBase.h"

NS_COLLADA_BEGIN

/*
 * image tag
 */
class Image:DocBase{
	InitFrom	m_init_from;
	std::string m_name;
	std::string m_id;

public:
	void initFromDoc(const CHAR_XML_NODE& doc);
};


/*
* LibImages ±Í«©
*/
class LibImages: DocBase
{
	std::vector<Image>	m_images;
public:
	void initFromDoc(const CHAR_XML_NODE& doc) { parseVecChildNode<std::vector<Image>, Image>(m_images, doc, "image"); }
};

NS_COLLADA_END
