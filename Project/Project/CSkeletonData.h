#pragma once

#include "ColladaDefine.h"
#include <vector>
#include "dae.h"

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

	void initWithElement(daeElementRef controller, daeElement* bone_root, daeDocument* doc, int p_id, CSkeletonData& skeleton);
	bool isBindValid();
	int getID(){ return m_ID;};

private:
	int		m_ID=0;		// id of this bone
	int		m_ParentID=0;		// parent id of this bone
	CMatrix4f     *m_JointMatrix = {nullptr};				// The model matrix
	CMatrix4f     *m_InverseBindMatrix = {nullptr};			// The Inverse Bind Pose Matrix
	CMatrix4f     *m_WorldMatrix = {nullptr};				// The World Matrix, should cal every frame, it is a tmp mat
	CMatrix4f     *m_SkinningMatrix = {nullptr};			// The Matrix Used for calculations

	std::vector<int>   m_Children;
	std::vector<CKeyframe*> m_Keyframes;					// all key frames for this Bone's animation
};


/*
 * �Ǽ�����
 * scene--->library_visual_scenes
 */
class CSkeletonData{
public:
	CSkeletonData(void);
	~CSkeletonData(void);

	void initWithElement(daeElementRef controller, daeElement* bone_root, daeDocument* doc);
	void loadJointInvMats(daeElementRef controller, daeDocument* doc);
	float* getInvMat(std::string sid);

	size_t getNoOfBones();
	bool addBone(CBone* bone_ptr);

private:
	unsigned int  m_NoOfKeyframes={0};		// ����ؼ�֡������զ�㣬 ÿ��CBone ���ܴ��ڵĹؼ�֡�ǲ�һ����
	CMatrix4f     *m_BindShapeMatrix={nullptr};

	std::vector<CBone*> m_Bones;
 	CBone         *m_RootBone={nullptr};
	std::hash_map<std::string, float*> m_InvMatMap;

	inline void deleteInvMatMap();
};
NS_C_DRAW_END
