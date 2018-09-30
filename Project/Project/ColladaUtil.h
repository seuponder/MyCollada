#pragma once

#include "ColladaDefine.h"

#ifdef COLLADA_DOM_SUPPORT141
#include "1.4/dom/domTypes.h"
using namespace ColladaDOM141;
#else
#include "1.4/dom/domTypes.h"
using namespace ColladaDOM150;
#endif

NS_C_DRAW_BEGIN

void assign_dom_float4(float* tar, domFloat4& src);

NS_C_DRAW_END