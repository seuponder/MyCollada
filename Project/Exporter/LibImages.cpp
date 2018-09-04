#include "LibImages.h"
#include "Common.h"
#include "Utils.h"

NS_COLLADA_BEGIN

void Image::initFromDoc(const CHAR_XML_NODE& doc)
{
	parseChildNode(m_init_from, doc, "init_from", "Image has no init_from node.");

	parseStrAttribute(m_id, doc, "id", "Image has no id attr.");
	parseStrAttribute(m_name, doc, "name", "Image has no name attr.");
}


NS_COLLADA_END