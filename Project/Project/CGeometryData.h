#pragma once

#include "ColladaDefine.h"
#include "dae.h"
#include <vector>

NS_C_DRAW_BEGIN

class CVertexInfluence{
public:
	CVertexInfluence(void);
	~CVertexInfluence(void);

	void init_with_indexes(size_t no_inf, unsigned int *weights, int* joints);

private:
	unsigned int	m_NoOfInflueneces = 0;
	unsigned int	*m_Weights = {nullptr}; // 存的是索引
	int				*m_Joints = {nullptr};
};

class CGeometryData{
public:
	CGeometryData(void)=default;
	~CGeometryData(void);

	// 加载数据
	void init_vertices_from_element(daeElement* element);
	void init_normals_from_element(daeElement* element);
	void init_texturecoords_from_element(daeElement* element);
	void init_vertexweight_from_element(daeElementRef controller, daeElement* bone_root, daeDocument* doc);

private:
	float		*m_VerticesArray = {nullptr};	// loaded
	float		*m_SkinnedVerticesArray = { nullptr };
	float		*m_NormalsArray = { nullptr };	// loaded
	float		*m_SkinnedNormalArray = { nullptr };
	float       *m_TextureCoordsArray = { nullptr };	// loaded
	float		*m_VertexWeightsArray = { nullptr };	// loaded
	std::vector<CVertexInfluence*>	*m_VertexInfluences = { nullptr };

	unsigned int	m_VerticesArraySize;
	unsigned int	m_NormalsArraySize;
	unsigned int	m_TextureCoordsArraySize;
	unsigned int	m_VertexWeightsArraySize;
};

NS_C_DRAW_END

