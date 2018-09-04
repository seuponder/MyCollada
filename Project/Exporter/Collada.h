/*
 * Collada dae 文件导出部分需要的一个格式
 * 本文件定义读入collada 需要的一些类
*/
#pragma once

#include "Common.h"
#include "LibGeometry.h"
#include "LibImages.h"
#include "LibMaterials.h"
#include "Utils.h"


NS_COLLADA_BEGIN

class Collada
{
	LibGeometry	m_lib_geometry;
	LibImages	m_lib_images;
	LibMaerials m_lib_materials;

public:

};

NS_COLLADA_END
