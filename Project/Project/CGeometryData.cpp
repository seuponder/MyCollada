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

/*
* �����ܹ���Ӱ������ݽṹ
*/
CVertexInfluence::~CVertexInfluence{
	SAFE_DELETE(m_Weights);
	SAFE_DELETE(m_Joints);
}

void CVertexInfluence::init_with_indexes(size_t no_inf, unsigned int *weights, int* joints){
	m_NoOfInflueneces = no_inf;
	SAFE_DELETE(m_Weights);
	SAFE_DELETE(m_Joints);

	m_Weights = new unsigned int[no_inf];
	m_Joints = new int[no_inf];

	for(size_t idx=0; idx < no_inf; idx ++){
		m_Weights[idx] = weight_idxs[idx];
		m_Joints[idx] = joints[idx];
	}
}

/* 
* CGeometry begin 
*/

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
 * ͨ��daeElement ��ʼ����������
 */
void CGeometryData::init_vertices_from_element(daeElement* element)
{
	if(m_VerticesArray != nullptr)
	{
		// �Ѿ���ʼ�����˾Ͳ������³�ʼ��
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
 * ��ʼ����������
 */
void CGeometryData::init_normals_from_element(daeElement* element)
{
	if (m_NormalsArray != nullptr)
	{
		// �Ѿ���ʼ�����˾Ͳ������³�ʼ��
		return;
	}
	auto dom = element->getChildrenByType<domFloat_array>()[0];		// smartref
	m_NormalsArraySize = dom->getCount();

	SAFE_DELETE(m_NormalsArray);
	m_NormalsArray = new float[m_NormalsArraySize];
	for (size_t idx = 0; idx < m_NormalsArraySize; idx++)
	{
		m_NormalsArray[idx] = dom->getValue()[idx];
	}
}

/*
 *  ��ʼ��uv ����
 */
void CGeometryData::init_texturecoords_from_element(daeElement* element)
{
	if (m_TextureCoordsArray != nullptr)
	{
		// �Ѿ���ʼ�����˾Ͳ������³�ʼ��
		return;
	}
	auto dom = element->getChildrenByType<domFloat_array>()[0];		// smartref
	m_TextureCoordsArraySize = dom->getCount();

	SAFE_DELETE(m_TextureCoordsArray);
	m_TextureCoordsArray = new float[m_TextureCoordsArraySize];
	for (size_t idx = 0; idx < m_TextureCoordsArraySize; idx++)
	{
		m_TextureCoordsArray[idx] = dom->getValue()[idx];
	}
}

/*
* ���ʼ��Ƥ��������
*/
void CGeometryData::init_vertexweight_from_element(daeElementRef controller, daeElement* bone_root, daeDocument* doc){
	auto dae = doc->getDAE();

	auto vw = controller->getDescendant("vertex_weights");
	auto input_vec = vw->getChildrenByType<domInputLocal>();
	size_t input_count = input_vec.getCount();
	size_t num_vex = std::stoi(vw->getAttribute("count"));

	// v�������Ƕ������ĸ��������е�Ӱ��
	auto v = (domV*) vw->getChild("v");
	auto v_value = v->getValue();
	auto vcount = (domVCount*) vw->getChild("vcount");
	auto v_count_value = v_count->getValue();
	std::vector<SkeletonSemantic> semantic_vec(input_count);

	// ��������
	std::vector<float> weights;		// Ȩ���б�
	std::vector<std::string> joints;	// �����б�

	for_each(auto input: input_vec){
		auto offset = std::stoi(input->getAttribute("offset"));

		if(!strcmp(input->getSemantic(), "JOINT")){
			// ��������
			// todo  ������ԭʼ����û�д洢

			semantic_vec[offset] = SkeletonSemantic::JOINT;
		}
		elif(!strcmp(input->getSemantic(), "WEIGHT")){
			// ����Ȩ��
			SAFE_DELETE(m_VertexWeightsArray);
			daeElement* weight_elment = dae->getDatabase()->idLookup(input->getAttribute("source"), doc);
			auto dom = weight_elment->getChildrenByType<domFloat_array>()[0];		// smartref
			m_VertexWeightsArraySize = dom->getCount();
			m_VertexWeightsArray = new float[m_VertexWeightsArraySize];

			for (size_t idx = 0; idx < m_VertexWeightsArraySize; idx++)
			{
				m_VertexWeightsArray[idx] = dom->getValue()[idx];
			}

			semantic_vec[offset] = SkeletonSemantic::WEIHGT;
		}
	}

	SAFE_DELETE(m_VertexInfluences);
	m_VertexInfluences = new std::vector<CVertexInfluence*>();
	unsigned int* weight_idxs = nullptr;
	int* joint_idxs = nullptr;

	size_t acc_idx = 0
	for(size_t vex_i=0; vex_i < num_vex < vex_i ++){
		size_t fluences_count = v_value.get(vex_i);		// ������ܹ���Ӱ�����Ŀ
		CVertexInfluence *p_vinf = new CVertexInfluence();

		SAFE_DELETE(weight_idxs);
		weight_idxs = new unsigned int[fluences_count];
		SAFE_DELETE(joint_idxs);
		joint_idxs = new int[fluences_count];

		for(size_t f_idx=0; f_idx < fluences_count; f_idx ++){
			joint_idxs[f_idx] = v_count_value.get(acc_idx + f_idx * input_count);
			weight_idxs[f_idx] = v_count_value.get(acc_idx + f_idx * input_count + 1);
		}
		p_vinf->init_with_indexes(fluences_count, weight_idxs, joint_idxs);
		*m_VertexInfluences[vex_i] = p_vinf;

		acc_idx += fluences_count * input_count;
	}
}

NS_C_DRAW_END
