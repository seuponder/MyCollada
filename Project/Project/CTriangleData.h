#pragma once

#include <string>
#include "ColladaDefine.h"
#include "dae.h"
#include "ColladaRender.h"

NS_C_DRAW_BEGIN

/*
* ����
*/
class CMaterial
{
public:
	float m_Ambient[4] = { 0.5f, 0.5f, 0.5f, 1.0f };		// ������
	float m_Diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };		// ������, ���ֱ���õ�һ���������˹���todo ������չΪdiffuse ��ͼ
	float m_Specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };	// �߹�
	float m_Emmision[4] = { 0.0f, 0.0f, 0.0f, 1.0f };	// �Է���
	float m_Shine = { 45.0 };			// ��������hdr����Ĺ⻬��
	float m_Transparency = { 1.0 };
	std::string	m_TextureFileName;
	std::string m_MaterialID;		// todo �����������֪������������Ǹ��ֶ�

};

/*
 *  ������
 */
enum  TriangleSemantic
{
	VERTICE = 0,
	NORMAL,
	TEXTURE_UV		// ��ʱֻ֧��һ��ͨ��
};


class CTriangle
{
public:
	CTriangle(void)=default;
	~CTriangle(void)=default;

	void init_with_indexes(std::vector<unsigned int>& idx_vec, std::vector<TriangleSemantic> &smantic_vec);

private:
	unsigned short m_VerticesIndex[3];		// 3������
	unsigned short m_NormalsIndex[3];		// ��������
	unsigned short m_TexturesIndex[3];		// ������������
};

/*
 * �������飬���ղ��ʷ���
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