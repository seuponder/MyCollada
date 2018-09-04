/*
 * 通用函数
 */

#include "Utils.h"
#include "Common.h"


std::string getStringFromFile(const std::string& file_name)
{
	std::string ret = "";
	if(file_name.empty())
	{
		return ret;
	}

	// 不做路径转换
	size_t size = 0;
	size_t read_size = 0;	// 读取文件真实大小
	unsigned char* buffer = nullptr;
	do
	{
		
		FILE* fp = nullptr;
		auto err_no = fopen_s(&fp, file_name.c_str(), "rt");
		if (!fp)
		{
			std::string msg = "Open file(";
			msg.append(file_name).append(") failed!");
			Log("%s with errno: %d", msg.c_str(), err_no)
			break;
		}

		fseek(fp, 0, SEEK_END);
		size = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		buffer = (unsigned char*)malloc(sizeof(unsigned char) * (size + 1));
		buffer[size] = '\0';

		read_size = fread_s(buffer, size, sizeof(unsigned char), size, fp);
		fclose(fp);

		if(read_size < size)
		{
			buffer[read_size] = '\0';
		}

	} while (false);

	if(buffer == nullptr || read_size == 0)
	{
		std::string msg = "Get data from file(";
		msg.append(file_name).append(") failed!");
		Log("%s", msg.c_str());
	}
	else
	{
		std::string ret((const char*)buffer);
	}
	return ret;
}

void parseXmlFile(CHAR_XML_DOC& doc, std::string file_name)
{
	std::string content = getStringFromFile(file_name);
	if (content.empty())
	{
		return;
	}

	doc.parse<0>(const_cast<char*>(content.c_str()));

}

// 解析int 属性
void parseIntAttribute(uint16_t& target, const CHAR_XML_NODE& doc, std::string attr_name, std::string fail_log)
{
	auto attr = doc.first_attribute(attr_name.c_str());
	if (attr == XML_NODE_NULL)
	{
		Log(fail_log.c_str());
	}
	else
	{
		target = std::stoi(attr->value());
	}
}

// 解析str属性
void parseStrAttribute(std::string& target, const CHAR_XML_NODE& doc, std::string attr_name, std::string fail_log)
{
	auto attr = doc.first_attribute(attr_name.c_str());
	if (attr == XML_NODE_NULL)
	{
		Log(fail_log.c_str());
	}
	else
	{
		target = attr->value();
	}
}



