/*
 * �ļ����أ� �����м��ʽ��ȡ����Ҫ����ֱ�Ӵ�dae �ļ��г�ȡ��Ⱦʹ�õļ�����
 * 
 */
#pragma once

#include "ColladaDefine.h"
#include "ColladaRender.h"
#include "dae/daeDocument.h"

NS_C_DRAW_BEGIN

class DaeLoader{
public:
	void loadDaeFile(ColladaRender& render, std::string& file_name);

	void loadGeometryData(ColladaRender& render, daeDocument* doc);

	void loadTriangleGroup(ColladaRender& render, daeElementRef element);

	void loadSkelletonData(ColladaRender& render, daeDocument* doc);

};
NS_C_DRAW_END

