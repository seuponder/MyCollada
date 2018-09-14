#include "CTriangleData.h"
#include "ColladaDefine.h"
#include "dae.h"
#include <unordered_map>


#ifdef COLLADA_DOM_SUPPORT141
#include "1.4/dom/domP.h"
#include "1.4/dom/domInputLocal.h"
using namespace ColladaDOM141;
#else
#include "1.5/dom/domP.h"
#include "1.5/dom/domInput_local.h"
using namespace ColladaDOM150;
typedef domInput_local domInputLocal;
#endif


NS_C_DRAW_BEGIN
/*
 *  三角形的初始化
 *  传入按照特定的语义吧[v_0, n_0, t_0, v_1, n_1, t_1, v_2, n_2, t_2,]
 *  
 */
void CTriangle::init_with_indexes(std::vector<unsigned int>& idx_vec, std::vector<TriangleSemantic> &smantic_vec)
{
	size_t idx_size = idx_vec.size();
	size_t semantic_size = smantic_vec.size();

	if(idx_size != semantic_size * 3)
	{
		Log("CTriangle::init_with_indexes the idx size： %d is not match smantic_vec: %d", idx_size, semantic_size);
		return;
	}

	for (size_t i=0; i < 3; i++)
	{
		for (size_t s_idx=0; s_idx < semantic_size; s_idx ++)
		{
			if(smantic_vec[s_idx] == VERTICE)
			{
				m_VerticesIndex[i] = idx_vec[i * semantic_size + s_idx];
			}

			if (smantic_vec[s_idx] == NORMAL)
			{
				m_NormalsIndex[i] = idx_vec[i * semantic_size + s_idx];
			}

			if (smantic_vec[s_idx] == TEXTURE_UV)
			{
				m_TexturesIndex[i] = idx_vec[i * semantic_size + s_idx];
			}
		}
	}
}


void CTriangleGroup::init_from_element(daeElementRef element, ColladaRender& render)
{
	m_NoOfTriangles = std::stoi(element->getAttribute("count"));

	// 解析input
	auto children = element->getChildrenByType<domInputLocal>();
	size_t input_num = children.getCount();

	std::vector<TriangleSemantic> semantic_vec(input_num);
	for (size_t i=0; i < input_num; i++)
	{
		auto child = children.get(i);
		auto offset = std::stoi(child->getAttribute("offset"));

		if(!strcmp(child->getSemantic(), "VERTEX"))
		{
			semantic_vec[offset] = VERTICE;
		}
		if (!strcmp(child->getSemantic(), "NORMAL"))
		{
			semantic_vec[offset] = NORMAL;
		}
		if (!strcmp(child->getSemantic(), "TEXCOORD"))
		{
			semantic_vec[offset] = TEXTURE_UV;
		}

	}

	// 释放索引
	SAFE_DELETE_ARR(m_Triangles);
	m_Triangles = new CTriangle[m_NoOfTriangles];


	// 初始化索引
	auto p = (domP*) element->getChild("p");
	auto p_value = p->getValue();
	std::vector<unsigned int> idx_vec(3 * input_num);

	for(int i=0; i< m_NoOfTriangles; i++)
	{
		for (size_t lv_idx=0; lv_idx < 3; lv_idx ++)
		{
			for (size_t j = 0; j < input_num; j++)
			{
				auto attr_idx = p_value.get(i * input_num * lv_idx + j);
				idx_vec[lv_idx * input_num + j] = attr_idx;
			}
		}

		CTriangle tri;
		tri.init_with_indexes(idx_vec, semantic_vec);
		m_Triangles[i] = tri;
	}
}

NS_C_DRAW_END