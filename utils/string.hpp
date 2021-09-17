#ifndef _STRUTILS_HPP_
#define _STRUTILS_HPP_

#include <iostream>
#include <vector>


class StringUtils
{
public:
  StringUtils();
  ~StringUtils();

public:
  std::string chToHex(unsigned char ch);
  std::string strToHex(std::string str, std::string separator);
  std::vector<unsigned char> StringUtils::strToCharArr(const char *str);
  std::string binToHex(const unsigned char *data, size_t size);
  std::vector<unsigned char> hexToBin(const std::string &hex);
};

#endif // _STRUTILS_HPP_



