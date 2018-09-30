/*
 * ������򵥵� ֻ�Ƕ�һ��mesh
 * ��������û��model ֮��ĸ��Σ�����ֱ���Ƿ���TriangleGroup [�������Ϊsub mesh]
 * 
 */

#pragma once
#include "ColladaDefine.h"
#include "CGeometryData.h"
#include "CTriangleData.h"
#include "CSkeletonData.h"
#include "CTriangleData.h"

NS_C_DRAW_BEGIN

class ColladaRender{
	friend class DaeLoader;

public:
	ColladaRender(void);
	~ColladaRender(void);

	void Draw();
	bool Update(unsigned long mili_seconds);
	void SetupSkeleton(int frame);
	void SetupBindPose();
	
	void loadDae(std::string file_name);		// �������������Ҫ��Ⱦ�ĳ�Աɨ����
	void initSkeletonDataFromElement(daeElementRef controller, daeElement* bone_root, daeDocument* doc);			// ����skeleton ����

protected:
	void CalculateBound();
	void ConvertToArrays();

private:
	
	CGeometryData	*m_geometry_data={nullptr};	// Common data in the mesh (List of Vertices/Normals/TexCoords)
	CSkeletonData	*m_skeleton_data={nullptr};	// Skelleton Data used for animation
	std::vector<CTriangleGroup>	m_triangle_groups;	// Individual Triangle Grtoups Sepatated By material Data
};

NS_C_DRAW_END