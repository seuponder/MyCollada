/*
 * some common definition
 */
#pragma once
#include <iostream>
#include "lib/rapidxml.hpp"

/*
 * �������ϵĽӿ�
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
 * ����
 */
typedef  rapidxml::xml_node<char>	CHAR_XML_NODE;
typedef  rapidxml::xml_document<char>	CHAR_XML_DOC;

#define  XML_NODE_NULL 0