#include "Common.h"
#include "LibGeometry.h"
#include "Utils.h"

// 直接用boost
// boost 是用Tools/NuGet Package Manager 直接安装的，还挺快， 挺好用
// 可以自己下载配置的，最好是写好cmake, 这样可以复用
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

NS_COLLADA_BEGIN

/*
 * FloatArray
 */
void FloatArray::initFromDoc(const CHAR_XML_NODE& doc)
{
	// id
	parseStrAttribute(m_id, doc, "id", "FloatArray has not id.");

	// count
	parseIntAttribute(m_count, doc, "count", "FloatArray has not count.");

	// 数组
	std::string value_str = doc.value();
	std::vector<std::string> vec_str;
	boost::split(vec_str, value_str, boost::is_any_of(" "), boost::token_compress_on);

	// 释放 
	SAFE_DELETE(m_data);

	if(!vec_str.empty())
	{
		m_data = (float*)malloc(vec_str.size() * sizeof(float));

		for (std::string sub_str : vec_str)
		{
			*m_data++ = std::stof(sub_str);
		}
	}

}


/*
 * NameArray
 */
void NameArray::initFromDoc(const CHAR_XML_NODE& doc)
{
	// id
	parseStrAttribute(m_id, doc, "id", "NameArray has not id.");

	// count
	parseIntAttribute(m_count, doc, "count", "NameArray has not count.");

	// 数组
	std::string value_str = doc.value();
	std::vector<std::string> vec_str;
	boost::split(vec_str, value_str, boost::is_any_of(" "), boost::token_compress_on);

	// 清空
	m_data.clear();

	if (!vec_str.empty())
	{
		for (std::string sub_str : vec_str)
		{
			m_data.push_back(sub_str);
		}
	}
}


/*
 * Param
 */
void Param::initFromDoc(const CHAR_XML_NODE& doc)
{
	// name
	parseStrAttribute(m_name, doc, "name", "Param has not name.");

	// type
	parseStrAttribute(m_type, doc, "type", "Param has not type.");

}


/*
 * Accessor
 */
void Accessor::initFromDoc(const CHAR_XML_NODE& doc)
{
	// count
	parseIntAttribute(m_count, doc, "count", "Accessor has not count.");


	// stride
	parseIntAttribute(m_stride, doc, "stride", "Accessor has not stride.");

	// source
	parseStrAttribute(m_source, doc, "source", "Accessor has not source.");

	// params
	parseVecChildNode<std::vector<Param>, Param>(m_params, doc, "param");
}

/*
 * TechniqueCommon
 */
void TechniqueCommon::initFromDoc(const CHAR_XML_NODE& doc)
{
	parseChildNode(m_accessor, doc, "accessor", "TechniqueCommon has no technique common accessor.");
}


/*
 * Source
 */
template <typename T>
void Source<T>::initFromDoc(const CHAR_XML_NODE& doc)
{
	// id
	parseStrAttribute(m_id, doc, "id", "Source has not id.");

	// technique
	parseChildNode(m_technique_common, doc, "technique_common", "Source has no technique common node.");

	// array
	auto name_arr = doc.first_node("Name_array");
	if(name_arr != XML_NODE_NULL)
	{
		parseChildNode(m_array, doc, "Name_array", "");
	}

	auto float_arr = doc.first_node("float_array");
	if (float_arr != XML_NODE_NULL)
	{
		parseChildNode(m_array, doc, "float_array", "");
	}
}

/*
 * Input
 */
void Input::initFromDoc(const CHAR_XML_NODE& doc)
{
	parseStrAttribute(m_semantic, doc, "semantic", "Input has not semantic.");

	parseStrAttribute(m_source, doc, "source", "Input has not source");

	parseIntAttribute(m_offset, doc, "offset", "Input has not offset");
	parseIntAttribute(m_set, doc, "set", "Input has not set");
}


/*
 * Vertices
 */
void Vertices::initFromDoc(const CHAR_XML_NODE& doc)
{
	parseStrAttribute(m_id, doc, "id", "Vertices has not id");

	// params
	parseVecChildNode<std::vector<Input>, Input>(m_inputs, doc, "input");
}


/*
 * P
 */
void P::initFromDoc(const CHAR_XML_NODE& doc)
{
	// 数组
	std::string value_str = doc.value();
	std::vector<std::string> vec_str;
	boost::split(vec_str, value_str, boost::is_any_of(" "), boost::token_compress_on);

	// 释放 
	SAFE_DELETE(m_indices);
	m_count = 0;

	if (!vec_str.empty())
	{
		m_count = vec_str.size();
		m_indices = (uint16_t*)malloc(m_count * sizeof(uint16_t));

		for (std::string sub_str : vec_str)
		{
			*m_indices++ = (uint16_t) std::stoi(sub_str);
		}
	}
}


/*
 * Triangles
 */
void Triangles::initFromDoc(const CHAR_XML_NODE& doc)
{
	parseStrAttribute(m_material, doc, "material", "Triangles has no materials attr.");
	parseIntAttribute(m_count, doc, "count", "Triangles has no count attr.");

	parseChildNode(m_p, doc, "p", "Triangles has no P node.");
	parseVecChildNode<std::vector<Input>, Input>(m_inputs, doc, "input");
}

/*
 * Mesh
 */
void Mesh::initFromDoc(const CHAR_XML_NODE& doc)
{
	parseVecChildNode<std::vector<Triangles>, Triangles>(m_triangles, doc, "triangles");
	parseVecChildNode<std::vector<Source<FloatArray>>, Source<FloatArray>>(m_sources, doc, "source");

	parseChildNode(m_vertices, doc, "vertices", "Mesh has no Vertices node.");
}


/*
 * Geometry
 */
void Geometry::initFromDoc(const CHAR_XML_NODE& doc)
{
	parseStrAttribute(m_id, doc, "id", "Geometry has no id attr.");
	parseStrAttribute(m_name, doc, "name", "Geometry has no name attr.");

	parseChildNode(m_mesh, doc, "mesh", "Geometry has no mesh node.");
}

/*
 * LibGeometry
 */
void LibGeometry::initFromDoc(const CHAR_XML_NODE& doc)
{
	parseVecChildNode<std::vector<Geometry>, Geometry>(m_geometries, doc, "geometry");
}

NS_COLLADA_END