#pragma once

#include "ColladaDefine.h"
#include <vector>

NS_C_DRAW_BEGIN

/*
 * library_animation ��dae�ļ����ݽṹ
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
 *  ������������
 *  ����joint �ؽڵ����ݣ� ����������������ؽ�֮��Ĺ�����ֻ��Ϊ����������
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
	CKeyframe     **m_Keyframes;				// All Key frames for this Bone��s animation
};


/*
 * �Ǽ�����
 * scene--->library_visual_scenes
 */
class CSkeletonData{
public:
	CSkeletonData(void);
	~CSkeletonData(void);

	void initWithElement();

private:
	unsigned int  m_NoOfBones={0};
	unsigned int  m_NoOfKeyframes={0};		// ����ؼ�֡������զ�㣬 ÿ��CBone ���ܴ��ڵĹؼ�֡�ǲ�һ����
	CMatrix4f     *m_BindShapeMatrix={nullptr};

	CBone         **m_Bones={nullptr};
	CBone         *m_RootBone={nullptr};
};
NS_C_DRAW_END
