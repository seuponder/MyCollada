/*
 * ͨ�ú����ļ�
 */
#pragma once

#include "lib/rapidxml.hpp"
#include <string>
#include <vector>

#include "Common.h"

/*
 * ����xml�ļ�
 */
std::string getStringFromFile(const std::string& file_name);
void parseXmlFile(CHAR_XML_DOC& doc, std::string file_name);

void parseIntAttribute(uint16_t& target, const CHAR_XML_NODE& doc, std::string attr_name, std::string fail_log);
void parseStrAttribute(std::string& target, const CHAR_XML_NODE& doc, std::string attr_name, std::string fail_log);


/*
 * ģ�庯���������Ͷ��嶼д��.h �ļ��У� �ܹ���֤��ʵ������ʱ���ܹ�ʵ����
 * ��Ȼ�����Ӵ���,
 * 
 * ԭ����ǵ�ʹ��ģ�庯�����ļ��У�#include ��Utils.h ��ʱ�� ���ֻ�������Ļ��� ģ�庯����û�취ʵ����
 * ��ô�Ƶ�������ģ�庯��ʵ����ֻ����һ���ⲿ���Ŵ洢�ڱ���õ�.o�ļ��У� �����ӵ�ʱ��ȴ���ⲿû�취�ҵ�ʵ�����Ĵ���
 * �ͻᱨ���Ӵ���
 * 
 * ����һ�ְ취������������.h�ļ��У�����[ʵ��]��cpp �ļ����棬Ȼ����.h �ļ���ǿ��ʵ�������������������� ֻ������ʵ����
 * ���������޵�����Ż�ȽϷ��㣬��Ȼ������Ҫ��һ��ʵ��������������Ƚϵ���
 */

/*
* ����list�ӽڵ�
* NodeType ��Ҫ�����������ɵĶ��������
* T vectorʵ������������
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
* ������node
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