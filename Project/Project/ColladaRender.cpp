#include "ColladaRender.h"
#include "ColladaDefine.h"

NS_C_DRAW_BEGIN

/*
 * ����dae �ļ�������ݳ�Ա
 * Ϊ��Ⱦ��׼��
 */
void ColladaRender::loadDae(std::string file_name)
{
	
}

/*
 * ���캯��
 */
ColladaRender::ColladaRender()
{
	
}

/*
 * ��������
 */
ColladaRender::~ColladaRender()
{
	SAFE_DELETE(m_geometry_data);
	SAFE_DELETE(m_skeleton_data);

	m_triangle_groups.clear();
}

/*
 * ��ʼ��skeleton����
 * controller 
 */
void ColladaRender::initSkeletonDataFromElement(daeElementRef controller, daeElement* bone_root, daeDocument* doc)
{
	// ��ʼ�� ����
	SAFE_DELETE(m_skeleton_data);
	m_skeleton_data = new CSkeletonData();
	m_skeleton_data->initWithElement(controller, bone_root, doc);

	// ��ʼ����Ƥ����
	m_geometry_data->init_vertexweight_from_element(controller, bone_root, doc);

}

NS_C_DRAW_END