#pragma once

#include "ColladaDefine.h"
#include <vector>

NS_C_DRAW_BEGIN

class CKeyframe{
public:
	CKeyframe(void);
	~CKeyframe(void);

private:
	float	m_Time;				// Time of this key frame
	CMatrix4f	*m_Transform;	// Transform of this Key frame
};


/*
 *  单根骨骼数据
 */
class CBone{
public:
	CBone(void);
	~CBone(void);

private:
	int		m_ID;		// id of this bone
	int		m_ParentID;		// parent id of this bone
	CMatrix4f     *m_JointMatrix;				// The Bind Pose Matrix
	CMatrix4f     *m_InverseBindMatrix;			// The Inverse Bind Pose Matrix
	CMatrix4f     *m_WorldMatrix;				// The World Matrix
	CMatrix4f     *m_SkinningMatrix;			// The Matrix Used for calculations
	unsigned int  m_ChildCount;
	std::vector<int>   *m_Children;
	unsigned int  m_NoOfKeyframes;				// No Of key frames of animation for this bone
	CKeyframe     **m_Keyframes;				// All Key frames for this Bone’s animation
};


/*
 * 骨架数据
 */
class CSkeletonData{
public:
	CSkeletonData(void);
	~CSkeletonData(void);

private:
	unsigned int  m_NoOfBones;
	unsigned int  m_NoOfKeyframes;
	CMatrix4f     *m_BindShapeMatrix;

	CBone         **m_Bones;
	CBone         *m_RootBone;
};
NS_C_DRAW_END
