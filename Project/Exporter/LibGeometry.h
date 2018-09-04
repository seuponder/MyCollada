/*
 * reader about library_geometry tag
 */
#pragma once

#include "DocBase.h"
#include "Common.h"
#include <string>
#include <vector>
#include <memory>
#include "lib/rapidxml.hpp"

NS_COLLADA_BEGIN


/*
 * float array
 */
class FloatArray: DocBase {
	std::string m_id;
	uint16_t m_count = {0};
	float* m_data = {nullptr};

public:
	void initFromDoc(const CHAR_XML_NODE& doc);
	~FloatArray() { SAFE_DELETE(m_data); }
};

/*
 * name array
 */
class NameArray: DocBase
{
	std::string m_id;
	uint16_t m_count = {0};
	std::vector<std::string>	m_data;

public:
	void initFromDoc(const CHAR_XML_NODE& doc);

	~NameArray() { m_data.clear(); }
};

/*
 * tag param
 */
class Param: DocBase{
	std::string	m_name;
	std::string m_type;		// 参数类型

public:
	void initFromDoc(const CHAR_XML_NODE& doc);
};


/*
 * tag accessor
 */
class Accessor: DocBase
{
	uint16_t m_count = {0};
	uint16_t m_stride = {0};
	std::string m_source;
	std::vector<Param> m_params;
	
public:
	void initFromDoc(const CHAR_XML_NODE& doc);

	~Accessor() { m_params.clear(); };
};

/*
 * tag technique common
 */
class TechniqueCommon: DocBase
{
	Accessor m_accessor;

public:
	void initFromDoc(const CHAR_XML_NODE& doc);
};

/*
 * tag source
 */
template <typename T>
class Source: DocBase
{
	std::string m_id;
	T m_array;	// FloatArray or NameArray
	TechniqueCommon m_technique_common;

public:
	void initFromDoc(const CHAR_XML_NODE& doc);
};


/*
 * tag input
 */
class Input: DocBase
{
	std::string m_semantic;
	std::string m_source;
	uint16_t m_offset = {0};
	uint16_t m_set = {0};

public:
	void initFromDoc(const CHAR_XML_NODE& doc);
};


/*
 * tag vetices
 */
class Vertices: DocBase
{
	std::string m_id;
	std::vector<Input>	m_inputs;

public:
	void initFromDoc(const CHAR_XML_NODE& doc);

	~Vertices() { m_inputs.clear(); }
};

/*
* tag p
*/
class P : DocBase
{
	uint16_t m_count = { 0 };
	uint16_t* m_indices = { nullptr };

	
public:
	void initFromDoc(const CHAR_XML_NODE& doc);

	~P() { SAFE_DELETE(m_indices); }
};

/*
 * tag Triangles
 */
class Triangles: DocBase
{
	uint16_t m_count = {0};
	std::string m_material;		// 材质名字
	std::vector<Input>	m_inputs;
	P	m_p;

public:
	void initFromDoc(const CHAR_XML_NODE& doc);

	~Triangles() { m_inputs.clear(); }
};

/*
 * mesh tag
 */
class Mesh: DocBase{
	std::vector<Source<FloatArray>> m_sources;
	std::vector<Triangles> m_triangles;
	Vertices m_vertices;

public:
	~Mesh() { m_sources.clear(); m_triangles.clear(); }
	void initFromDoc(const CHAR_XML_NODE& doc);
};


/*
 * gepmetry tag
 */
class Geometry: DocBase{
public:
	void initFromDoc(const CHAR_XML_NODE& doc);

private:
	std::string m_id;
	std::string m_name;

	Mesh m_mesh;
};

/*
 * library_geometry tag
 */
class LibGeometry: DocBase{

private:
	std::vector<Geometry> m_geometries;		// 包含的所有geometry

public:
	~LibGeometry() { m_geometries.clear(); }

	void initFromDoc(const CHAR_XML_NODE& doc);

};

NS_COLLADA_END