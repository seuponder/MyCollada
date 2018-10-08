#include "ColladaRender.h"
#include "ColladaDefine.h"

NS_C_DRAW_BEGIN

/*
 * 加载dae 文件填充数据成员
 * 为渲染做准备
 */
void ColladaRender::loadDae(std::string file_name)
{
	
}

/*
 * 构造函数
 */
ColladaRender::ColladaRender()
{
	
}

/*
 * 析构函数
 */
ColladaRender::~ColladaRender()
{
	SAFE_DELETE(m_geometry_data);
	SAFE_DELETE(m_skeleton_data);

	m_triangle_groups.clear();
}

/*
 * 初始化skeleton数据
 * controller 
 */
void ColladaRender::initSkeletonDataFromElement(daeElementRef controller, daeElement* bone_root, daeDocument* doc)
{
	// 初始化 骨骼
	SAFE_DELETE(m_skeleton_data);
	m_skeleton_data = new CSkeletonData();
	m_skeleton_data->initWithElement(controller, bone_root, doc);

	// 初始化蒙皮数据
	m_geometry_data->init_vertexweight_from_element(controller, bone_root, doc);

}

NS_C_DRAW_END