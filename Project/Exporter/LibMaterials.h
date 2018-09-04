/*
 * reader about library_materials
 */

#pragma once

#include "Common.h"
#include "Utils.h"
#include "DocBase.h"

NS_COLLADA_BEGIN

/*
 * tag instance_effect
 */
class InstanceEffect:DocBase{
	std::string m_url;

public:
	void initFromDoc(const CHAR_XML_NODE& doc) { parseStrAttribute(m_url, doc, "url", "InstanceEffect has no url attr."); }
};


/*
 * tag material
 */
class Material:DocBase{
	std::string	m_id;
	std::string m_name;
	InstanceEffect	m_instance_effect;

public:
	void initFromDoc(const CHAR_XML_NODE& doc);

};

/*
 * tag library_materials
 */
class LibMaerials:DocBase{
	std::vector<Material>	m_materials;

public:
	void initFromDoc(const CHAR_XML_NODE& doc) { parseVecChildNode < std::vector<Material>, Material>(m_materials, doc, "material"); }
};

NS_COLLADA_END