#pragma once

#include <string>
#include "ColladaDefine.h"
#include "dae.h"
#include "ColladaRender.h"

NS_C_DRAW_BEGIN

/*
* 材质
*/
class CMaterial
{
public:
	float m_Ambient[4] = { 0.5f, 0.5f, 0.5f, 1.0f };		// 环境光
	float m_Diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };		// 漫反射, 这边直接用的一个向量简化了哈，todo 可以扩展为diffuse 贴图
	float m_Specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };	// 高光
	float m_Emmision[4] = { 0.0f, 0.0f, 0.0f, 1.0f };	// 自发光
	float m_Shine = { 45.0 };			// 看起来是hdr里面的光滑度
	float m_Transparency = { 1.0 };
	std::string	m_TextureFileName;
	std::string m_MaterialID;		// todo 这个东西还不知道具体表现是那个字段

};

/*
 *  三角形
 */
enum  TriangleSemantic
{
	VERTICE = 0,
	NORMAL,
	TEXTURE_UV		// 暂时只支持一个通道
};


class CTriangle
{
public:
	CTriangle(void)=default;
	~CTriangle(void)=default;

	void init_with_indexes(std::vector<unsigned int>& idx_vec, std::vector<TriangleSemantic> &smantic_vec);

private:
	unsigned short m_VerticesIndex[3];		// 3个顶点
	unsigned short m_NormalsIndex[3];		// 发现索引
	unsigned short m_TexturesIndex[3];		// 纹理坐标索引
};

/*
 * 三角形组，按照材质分类
 */
class CTriangleGroup
{
public:
	CTriangleGroup(void);
	~CTriangleGroup(void);
	void init_from_element(daeElementRef element, ColladaRender& render);

private:
	CTriangle		*m_Triangles;
	CMaterial		*m_Material;
	unsigned int	m_NoOfTriangles;
};

NS_C_DRAW_END