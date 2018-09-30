#pragma once

#include "ColladaDefine.h"
#include "dae.h"
#include <vector>

NS_C_DRAW_BEGIN

class CVertexInfluence{
public:
	CVertexInfluence(void);
	~CVertexInfluence(void);

private:
	unsigned int	m_NoOfInflueneces;
	unsigned int	*m_Weights;
	int				*m_Joints;
};

class CGeometryData{
public:
	CGeometryData(void)=default;
	~CGeometryData(void);

	// º”‘ÿ ˝æ›
	void init_vertices_from_element(daeElement* element);
	void init_normals_from_element(daeElement* element);
	void init_texturecoords_from_element(daeElement* element);

private:
	float		*m_VerticesArray = {nullptr};	// loaded
	float		*m_SkinnedVerticesArray = { nullptr };
	float		*m_NormalsArray = { nullptr };	// loaded
	float		*m_SkinnedNormalArray = { nullptr };
	float       *m_TextureCoordsArray = { nullptr };	// loaded
	float		*m_VertexWeightsArray = { nullptr };
	std::vector<CVertexInfluence*>	*m_VertexInfluences = { nullptr };

	unsigned int	m_VerticesArraySize;
	unsigned int	m_NormalsArraySize;
	unsigned int	m_TextureCoordsArraySize;
	unsigned int	m_VertexWeightsArraySize;
};

NS_C_DRAW_END

