#pragma once

#define NS_C_DRAW_BEGIN	namespace ColladaDraw{
#define NS_C_DRAW_END }

typedef float CMatrix4f[16];

/*
* log
*/
#define Log(...) {fprintf(stderr, "%s, LINE:%d \t", __FILE__, __LINE__);\
	fprintf(stderr, __VA_ARGS__);\
	}

/*
* const macro
*/
#define SAFE_DELETE(ptr) if(ptr != nullptr){\
		delete ptr;\
		ptr = nullptr;\
	}

#define SAFE_DELETE_ARR(ptr) if(ptr != nullptr){\
	delete []ptr;\
	ptr = nullptr;\
	}
 
#ifdef COLLADA_DOM_SUPPORT141
#define USING_DOM_NS using namespace ColladaDOM141;
#else
#define USING_DOM_NS using namespace ColladaDOM150;
#endif


#define  DAE_NULL 0

/*
 *  骨骼语意
 */
enum  SkeletonSemantic
{
	JOINT = 0,  // 骨骼
	WEIGHT,     // 权重
	INV_BIND_MATRIX		// 逆向绑定矩阵
};
