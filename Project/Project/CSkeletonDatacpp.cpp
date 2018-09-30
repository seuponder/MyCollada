#include "CSkeletonData.h"
#include "ColladaDefine.h"

NS_C_DRAW_BEGIN

CSkeletonData::~CSkeletonData()
{
	SAFE_DELETE(m_RootBone);
	SAFE_DELETE(m_BindShapeMatrix);

	m_Bones = nullptr;
}

NS_C_DRAW_END