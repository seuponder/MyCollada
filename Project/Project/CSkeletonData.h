#pragma once

#include "ColladaDefine.h"
#include <vector>

NS_C_DRAW_BEGIN

/*
 * library_animation 的dae文件数据结构
 *					channel
 *					   |
 *				/             \
 *			sampler			 target[bone]
 *					 
 */
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
 *  就是joint 关节的数据， 并不是真的是两个关节之间的骨骼，只是为了命名方便
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
 * scene--->library_visual_scenes
 */
class CSkeletonData{
public:
	CSkeletonData(void);
	~CSkeletonData(void);

	void initWithElement();

private:
	unsigned int  m_NoOfBones={0};
	unsigned int  m_NoOfKeyframes={0};		// 这个关键帧的数量咋搞， 每个CBone 可能存在的关键帧是不一样的
	CMatrix4f     *m_BindShapeMatrix={nullptr};

	CBone         **m_Bones={nullptr};
	CBone         *m_RootBone={nullptr};
};
NS_C_DRAW_END
