#pragma once

#include "ColladaDefine.h"
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
	CGeometryData(void);
	~CGeometryData(void);

private:
	float		*m_VerticesArray = {nullptr};
	float		*m_SkinnedVerticesArray = { nullptr };
	float		*m_NormalsArray = { nullptr };
	float		*m_SkinnedNormalArray = { nullptr };
	float       *m_TextureCoordsArray = { nullptr };
	float		*m_VertexWeightsArray = { nullptr };
	std::vector<CVertexInfluence*>	*m_VertexInfluences = { nullptr };

	unsigned int	m_VerticesArraySize;
	unsigned int	m_NormalsArraySize;
	unsigned int	m_TextureCoordsArraySize;
	unsigned int	m_VertexWeightsArraySize;
};

NS_C_DRAW_END

