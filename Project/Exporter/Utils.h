/*
 * 通用函数文件
 */
#pragma once

#include "lib/rapidxml.hpp"
#include <string>
#include <vector>

#include "Common.h"

/*
 * 解析xml文件
 */
std::string getStringFromFile(const std::string& file_name);
void parseXmlFile(CHAR_XML_DOC& doc, std::string file_name);

void parseIntAttribute(uint16_t& target, const CHAR_XML_NODE& doc, std::string attr_name, std::string fail_log);
void parseStrAttribute(std::string& target, const CHAR_XML_NODE& doc, std::string attr_name, std::string fail_log);


/*
 * 模板函数的声明和定义都写在.h 文件中， 能够保证在实例化的时候能够实例化
 * 不然会链接错误,
 * 
 * 原理就是当使用模板函数的文件中，#include 了Utils.h 的时候， 如果只是声明的话， 模板函数将没办法实例化
 * 那么推导出来的模板函数实例将只是以一个外部符号存储在编译好的.o文件中， 在链接的时候却在外部没办法找到实例化的代码
 * 就会报链接错误
 * 
 * 另外一种办法，就是声明在.h文件中，定义[实现]在cpp 文件里面，然后，在.h 文件中强行实例化，不过这种做法， 只能是在实例化
 * 的种类有限的情况才会比较方便，不然，就需要有一堆实例化的声明，会比较蛋疼
 */

/*
* 解析list子节点
* NodeType 需要解析数据生成的对象的类型
* T vector实例化对象类型
*/
template <typename T, typename NodeType>
void parseVecChildNode(T& target, const CHAR_XML_NODE& doc, std::string node_name)
{
	for (CHAR_XML_NODE* node = doc.first_node(node_name.c_str()); node != XML_NODE_NULL; node = node->next_sibling(node_name.c_str()))
	{
		auto node_obj = NodeType();
		node_obj.initFromDoc(*node);
		target.push_back(node_obj);
	}
}

/*
* 解析子node
*/
template <typename T>
void parseChildNode(T& target, const CHAR_XML_NODE& doc, std::string node_name, std::string fail_log)
{
	CHAR_XML_NODE* node = doc.first_node(node_name.c_str());
	if (node != XML_NODE_NULL)
	{
		target.initFromDoc(*node);
	}
	else
	{
		if (!fail_log.empty())
		{
			Log(fail_log.c_str());
		}
	}
}