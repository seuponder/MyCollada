#include "CGeometryData.h"
#include "ColladaDefine.h"

#ifdef COLLADA_DOM_SUPPORT141
#include "1.4/dom/domFloat_array.h"
using namespace ColladaDOM141;
#else
#include "1.5/dom/domFloat_array.h"
using namespace ColladaDOM150;
typedef domInput_local domInputLocal;
#endif


NS_C_DRAW_BEGIN

CGeometryData::~CGeometryData()
{
	SAFE_DELETE(m_VerticesArray);
	SAFE_DELETE(m_SkinnedVerticesArray);
	SAFE_DELETE(m_NormalsArray);
	SAFE_DELETE(m_SkinnedNormalArray);
	SAFE_DELETE(m_TextureCoordsArray);
	SAFE_DELETE(m_VertexWeightsArray);

	if(m_VertexInfluences != nullptr)
	{
		m_VertexInfluences->clear();
	}
}


/*
 * 通过daeElement 初始化顶点数据
 */
void CGeometryData::init_vertices_from_element(daeElement* element)
{
	if(m_VerticesArray != nullptr)
	{
		// 已经初始化过了就不再重新初始化
		return;
	}
	auto dom = element->getChildrenByType<domFloat_array>()[0];		// smartref
	m_VerticesArraySize = dom->getCount();

	SAFE_DELETE(m_VerticesArray);
	m_VerticesArray = new float(m_VerticesArraySize);
	for (size_t idx =0 ; idx < m_VerticesArraySize; idx ++)
	{
		m_VerticesArray[idx] = dom->getValue()[idx];
	}
}

/*
 * 初始化法线数据
 */
void CGeometryData::init_normals_from_element(daeElement* element)
{
	if (m_NormalsArray != nullptr)
	{
		// 已经初始化过了就不再重新初始化
		return;
	}
	auto dom = element->getChildrenByType<domFloat_array>()[0];		// smartref
	m_NormalsArraySize = dom->getCount();

	SAFE_DELETE(m_NormalsArray);
	m_NormalsArray = new float(m_NormalsArraySize);
	for (size_t idx = 0; idx < m_NormalsArraySize; idx++)
	{
		m_NormalsArray[idx] = dom->getValue()[idx];
	}
}

/*
 *  初始化uv 坐标
 */
void CGeometryData::init_texturecoords_from_element(daeElement* element)
{
	if (m_TextureCoordsArray != nullptr)
	{
		// 已经初始化过了就不再重新初始化
		return;
	}
	auto dom = element->getChildrenByType<domFloat_array>()[0];		// smartref
	m_TextureCoordsArraySize = dom->getCount();

	SAFE_DELETE(m_TextureCoordsArray);
	m_TextureCoordsArray = new float(m_TextureCoordsArraySize);
	for (size_t idx = 0; idx < m_TextureCoordsArraySize; idx++)
	{
		m_TextureCoordsArray[idx] = dom->getValue()[idx];
	}
}

NS_C_DRAW_END
