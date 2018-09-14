/*
 * 文件加载， 不做中间格式抽取，主要负责直接从dae 文件中抽取渲染使用的简单数据
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

};
NS_C_DRAW_END

