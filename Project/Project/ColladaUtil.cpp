#include "ColladaUtil.h"

NS_C_DRAW_BEGIN

void assign_dom_float4(float* tar, domFloat4& src)
{
	if(tar == nullptr)
	{
		return;
	}
	for (size_t idx = 0; idx < 4; idx ++)
	{
		tar[idx] = src.get(idx);
	}
}

NS_C_DRAW_END