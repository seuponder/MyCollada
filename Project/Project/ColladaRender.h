/*
 * 先用最简单的 只是读一个mesh
 * 所以这里没有model 之类的钙盐，材质直接是放在TriangleGroup [可以理解为sub mesh]
 * 
 */

#pragma once
#include "ColladaDefine.h"
#include "CGeometryData.h"
#include "CTriangleData.h"
#include "CSkeletonData.h"

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
	void loadDae(std::string file_name);		// 加载数据填充需要渲染的成员扫数据

protected:
	void CalculateBound();
	void ConvertToArrays();

private:
	
	CGeometryData	*m_geometry_data;	// Common data in the mesh (List of Vertices/Normals/TexCoords)
	CSkeletonData	*m_skeleton_data;	// Skelleton Data used for animation
	std::vector<CTriangleGroup>	m_triangle_groups;	// Individual Triangle Grtoups Sepatated By material Data
};

NS_C_DRAW_END