#include "ColladaUtil.h"
#include <functional>

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

void assign_dom_float4(float* tar, std::string& src){
	if(tar == nullptr)
	{
		return;
	}

	// 数组
	std::vector<std::string> vec_str;
	boost::split(vec_str, src, boost::is_any_of(" "), boost::token_compress_on);

	// 释放 
	if(!vec_str.empty())
	{
		for (std::string sub_str : vec_str)
		{
			*tar++ = std::stof(sub_str);
		}
	}
}

void assign_dom_float4(float* tar, float* src){
	for(size_t i=0;i < 16, i++){
		*tar++ = *src++;
	}
}


size_t hash(std::string str){
	if(str.empty()){
		return 0;
	}
	return std::hash<std::string>{}(str);
}


size_t get_bone_id(std::string bone_id){
	return hash(bone_id);
}


template<typename T>
void delete_vector_ptr_member(std::vector<T*> vec){
	for(size_t i=0; i < vec.size(); i++){
		SAFE_DELETE(vec[i]);
	}
	vec.clear();
}

NS_C_DRAW_END