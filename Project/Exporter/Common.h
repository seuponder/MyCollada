/*
 * some common definition
 */
#pragma once
#include <iostream>
#include "lib/rapidxml.hpp"

/*
 * 兼容性老的接口
 */
// #define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1

/*
 *  collada ns begin end definistion
 */
#define NS_COLLADA_BEGIN	namespace Collada{
#define NS_COLLADA_END	}


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

/*
 * 类型
 */
typedef  rapidxml::xml_node<char>	CHAR_XML_NODE;
typedef  rapidxml::xml_document<char>	CHAR_XML_DOC;

#define  XML_NODE_NULL 0