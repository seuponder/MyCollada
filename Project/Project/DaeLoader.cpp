#include "DaeLoader.h"
#include "ColladaDefine.h"
#include "dae.h"
#include <iostream>

/*
 * dom
 */
#ifdef COLLADA_DOM_SUPPORT141
#include "1.4/dom/domMesh.h"
#include "1.4/dom/domTriangles.h"
#include "1.4/dom/domInstance_controller.h"
#else
#include "1.5/dom/domMesh.h"
#include "1.5/dom/domTriangles.h"
#include "1.5/dom/domInstance_controller.h"
#endif

USING_DOM_NS

NS_C_DRAW_BEGIN

void DaeLoader::loadDaeFile(ColladaRender& render, std::string& file_name)
{
	DAE dae;
	daeElement* root = dae.open(file_name.c_str());
	if (!root)
	{
		Log("Document import failed. %s\n", file_name.c_str());
		return;
	}

	// geometry
	loadGeometryData(render, root->getDocument());

	// triangle group
	// 在geometry 中会递归加载

	// skeleton
	loadSkelletonData(render, root->getDocument());

}

/*
 * 加载Geometry data
 * 都只是加载一个mesh, 假设只有一个pos, texture coordinate， normal
 */
void DaeLoader::loadGeometryData(ColladaRender& render, daeDocument* doc)
{
	// vertices
	auto root = doc->getDomRoot();
	auto dae = doc->getDAE();

	// 只对第一个mesh 处理
	auto meshes = dae->getDatabase()->typeLookup(domMesh::ID());
	if(meshes.empty())
	{
		Log("can not find any mesh nodes.\n");
		return;
	}

	auto mesh = meshes[0];

	// 从triangle 开始加载
	auto triangles = mesh->getChildrenByType<domTriangles>();
	for(size_t i = 0; i < triangles.getCount() ; i++)
	{
		loadTriangleGroup(render, triangles.get(i));
	}

}

/*
 * 在加载TriangleGroup 的时候会使用source 去加载 geometry data
 * param element triangles 节点指针
 */
void DaeLoader::loadTriangleGroup(ColladaRender& render, daeElementRef element)
{
	CTriangleGroup	grp;
	grp.init_from_element(element, render);

	// friend class
	render.m_triangle_groups.push_back(grp);

	// 加载对应的实际数据
	auto doc = element->getDocument();
	auto dae = element->getDAE();
	auto children = element->getChildrenByType<domInputLocal>();
	size_t input_num = children.getCount();
	for (size_t i = 0; i < input_num; i++)
	{
		auto child = children.get(i);

		daeElement* src_ele = dae->getDatabase()->idLookup(child->getAttribute("source"), doc);
		if (src_ele == DAE_NULL)
		{
			continue;;
		}
		std::string semantic = child->getAttribute("semantc");
		if(strcmp(semantic.c_str(), "VERTEX"))
		{
			render.m_geometry_data->init_vertices_from_element(src_ele);
		}
		if (strcmp(semantic.c_str(), "NORMAL"))
		{
			render.m_geometry_data->init_normals_from_element(src_ele);
		}
		if (strcmp(semantic.c_str(), "TEXCOORD"))
		{
			render.m_geometry_data->init_texturecoords_from_element(src_ele);
		}
	}
}

/*
 * 加载skeleton数据
 */
void DaeLoader::loadSkelletonData(class ColladaRender& render, daeDocument* doc)
{
	// 拿到instance_controller
	auto root = doc->getDomRoot();
	auto dae = doc->getDAE();
	auto dom_controller = root->getChildrenByType<domInstance_controller>()[0];

	// controller element 皮肤绑定数据
	auto controller_ele = dom_controller->getUrl().getElement();

	// first is root
	auto first_skeleton = dom_controller->getChild("skeleton");
	std::string root_id = first_skeleton->getCharData().substr(1);
	daeElement* bone_root_ele = dae->getDatabase()->idLookup(root_id, doc);

	render.initSkeletonDataFromElement(controller_ele, bone_root_ele, doc);

}

NS_C_DRAW_END
