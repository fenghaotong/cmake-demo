#include <iostream>
#include <string>      // std::string
#include <sstream>     // std::stringstream
#include <cstdio>
#include <iomanip>
#include "string.hpp"

// using namespace std;

StringUtils::StringUtils(){

}

StringUtils::~StringUtils(){

}
/**
 * #purpose	: 字符转十六进制
 * #note	: 不适用于汉字字符
 * #param ch    : 要转换成十六进制的字符
 * #return	: 接收转换后的字符串
 */
std::string StringUtils::chToHex(unsigned char ch)
{
	const std::string hex = "0123456789ABCDEF";
 
	std::stringstream ss;
	ss << hex[ch >> 4] << hex[ch & 0xf];
 
	return ss.str();
}
 
/**
 * #purpose	: 字符串转十六进制字符串
 * #note	: 可用于汉字字符串
 * #param str		: 要转换成十六进制的字符串
 * #param separator	: 十六进制字符串间的分隔符
 * #return	: 接收转换后的字符串
 */
std::string  StringUtils::strToHex(std::string str, std::string separator)
{
	const std::string hex = "0123456789ABCDEF";
	std::stringstream ss;
 
	for (std::string::size_type i = 0; i < str.size(); ++i)
		ss << hex[(unsigned char)str[i] >> 4] << hex[(unsigned char)str[i] & 0xf] << separator;
	
	return ss.str();
}

/**
 * 字符串转为字符数组
 */
std::vector<unsigned char> StringUtils::strToCharArr(const char* str) {
  
  std::string starting_str = str;
  std::vector<unsigned char> ending;
  ending.reserve(starting_str.size());
  for (int i = 0; i < starting_str.length(); i += 2) {
    std::string pair = "0x" + starting_str.substr(i, 2);
    // std::cout << pair << std::endl;
    ending.push_back(::strtol(pair.c_str(), 0, 16));
	}

  return ending;
}

/**
 * 字符数组转为字符串
 * 
 */

std::string StringUtils::binToHex(const unsigned char *data, size_t size)
{
	std::ostringstream strHex;
	strHex << std::hex << std::setfill('0');
	for (size_t i = 0; i < size; ++i) {
		strHex << std::setw(2)<<static_cast<unsigned int>(data[i]);
	}
	return strHex.str();
}
 
/**
 * 字符串转为字符数组
 *   
 */
std::vector<unsigned char> StringUtils::hexToBin(const std::string &hex)
{
	std::vector<unsigned char> dest;
	auto len = hex.size();
	dest.reserve(len / 2);
	for (decltype(len) i = 0; i < len; i += 2)
	{
		unsigned int element;
		std::istringstream strHex(hex.substr(i, 2));
		strHex >> std::hex >> element;
		dest.push_back(static_cast<unsigned char>(element));
	}
	return dest;
}
