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
#else
#include "1.5/dom/domMesh.h"
#include "1.5/dom/domTriangles.h"
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

	// skeleton

}

/*
 * ����Geometry data
 * ��ֻ�Ǽ���һ��mesh, ����ֻ��һ��pos, texture coordinate�� normal
 */
void DaeLoader::loadGeometryData(ColladaRender& render, daeDocument* doc)
{
	// vertices
	auto root = doc->getDomRoot();
	auto dae = doc->getDAE();

	// ֻ�Ե�һ��mesh ����
	auto meshes = dae->getDatabase()->typeLookup(domMesh::ID());
	if(meshes.empty())
	{
		Log("can not find any mesh nodes.\n");
		return;
	}

	auto mesh = meshes[0];

	// ��triangle ��ʼ����
	auto triangles = mesh->getChildrenByType<domTriangles>();
	for(size_t i = 0; i < triangles.getCount() ; i++)
	{
		loadTriangleGroup(render, triangles.get(i));
	}

}

/*
 * param element triangles �ڵ�ָ��
 */
void DaeLoader::loadTriangleGroup(ColladaRender& render, daeElementRef element)
{
	
}

NS_C_DRAW_END
