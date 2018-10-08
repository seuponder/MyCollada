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
void assign_dom_float4(float* tar, std::string& src);
void assign_dom_float4(float* tar, float* src);

size_t hash(std::string str);
size_t get_bone_id(std::string bone_id);

template<typename T>
void delete_vector_ptr_member(std::vector<T*> vec);

NS_C_DRAW_END