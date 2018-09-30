#include "CTriangleData.h"
#include "ColladaDefine.h"
#include "ColladaUtil.h"

#include "dae.h"
#include <unordered_map>


#ifdef COLLADA_DOM_SUPPORT141
#include "1.4/dom/domP.h"
#include "1.4/dom/domInputLocal.h"
#include "1.4/dom/domInstance_effect.h"
#include "1.4/dom/domCommon_color_or_texture_type.h"
using namespace ColladaDOM141;
#else
#include "1.5/dom/domP.h"
#include "1.5/dom/domInput_local.h"
#include "1.5/dom/domInstance_effect.h"
#include "1.4/dom/domCommon_color_or_texture_type.h"
using namespace ColladaDOM150;
typedef domInput_local domInputLocal;
#endif


NS_C_DRAW_BEGIN

/*
 * 材质初始化
 */
void CMaterial::init_from_material_id(std::string material_id, ColladaRender& render, daeDocument* doc)
{
	if(material_id.empty())
	{
		return;
	}

	auto dae = doc->getDAE();
	auto root = doc->getDomRoot();

	// materilal---->effect
	daeElement* mat_ele = dae->getDatabase()->idLookup(material_id, doc);
	if(mat_ele == DAE_NULL)
	{
		return;
	}
	auto dom_effect = mat_ele->getChildrenByType<domInstance_effect>()[0];
	auto effect_ele = dom_effect->getUrl().getElement();

	// 只读一个technique
	daeElement* technique_ele = dom_effect->getDescendant("technique");

	//	-ambient
	//	-ambient
	auto ambient_ele = technique_ele->getDescendant("ambient");
	domCommon_color_or_texture_type* dom_color_com = ambient_ele->getChildrenByType<domCommon_color_or_texture_type>()[0];
	auto dom_color = dom_color_com->getColor();
	assign_dom_float4(m_Ambient, dom_color->getValue());

	// -diffuse
	auto diffuse_ele = technique_ele->getDescendant("diffuse");
	domCommon_color_or_texture_type* diff_tex_com = diffuse_ele->getChildrenByType<domCommon_color_or_texture_type>()[0];
	auto diff_tex = diff_tex_com->getTexture();
	daeSidRef sampler_ref(diff_tex->getTexture(), technique_ele);
	std::string surface_sid = sampler_ref.resolve().elt->getDescendant("source")->getCharData();
	daeSidRef surface_ref(surface_sid, effect_ele);
	m_TextureFileName = surface_ref.resolve().elt->getDescendant("init_from")->getCharData();

	// -specular
	auto specular_ele = technique_ele->getDescendant("specular");
	domCommon_color_or_texture_type* spec_color_com = ambient_ele->getChildrenByType<domCommon_color_or_texture_type>()[0];
	auto spec_color = spec_color_com->getColor();
	assign_dom_float4(m_Specular, spec_color->getValue());

	// -emmision
	auto emission_ele = technique_ele->getDescendant("emission");
	domCommon_color_or_texture_type* emi_color_com = ambient_ele->getChildrenByType<domCommon_color_or_texture_type>()[0];
	auto emi_color = emi_color_com->getColor();
	assign_dom_float4(m_Emmision, emi_color->getValue());

	// -m_Shine
	auto shininess_ele = technique_ele->getDescendant("shininess");
	m_Shine = std::stof(shininess_ele->getDescendant("float")->getCharData());

	// -transparency
	auto trans_ele = technique_ele->getDescendant("transparency");
	m_Transparency = std::stof(trans_ele->getDescendant("float")->getCharData());

	m_MaterialID = material_id;

}

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

	// 初始化CMaterial
	SAFE_DELETE(m_Material);
	m_Material = new CMaterial();
	m_Material->init_from_material_id(element->getAttribute("material"), render, element->getDocument());

}

CTriangleGroup::~CTriangleGroup()
{
	SAFE_DELETE(m_Material);
	SAFE_DELETE_ARR(m_Triangles);
}


NS_C_DRAW_END