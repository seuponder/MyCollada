#include "LibMaterials.h"
#include "Common.h"
#include "Utils.h"

NS_COLLADA_BEGIN

void Material::initFromDoc(const CHAR_XML_NODE& doc)
{
	parseStrAttribute(m_id, doc, "id", "Material has no id attr.");
	parseStrAttribute(m_name, doc, "name", "Material has no name attr.");

	parseChildNode(m_instance_effect, doc, "instance_effect", "Material has no instance effect node.");
}

NS_COLLADA_END