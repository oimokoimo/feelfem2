#include <iostream>
#include "pairClass.hpp"

StrIntPair::StrIntPair(const char *strData, int dat)
{
  name = strData;
  code = dat;
}

StrIntPair::~StrIntPair() = default;

int operator==(const StrIntPair &siPair, const char *dat)
{
  return (siPair.name == dat);
}

int operator==(const StrIntPair &left, const StrIntPair &right)
{
  return (right.name == left.name);
}

// String String Pair
StrStrPair::StrStrPair(const char *pgName, const char *libName)
{
  first  = pgName;
  second = libName;
}

StrStrPair::StrStrPair(const char *pre)
{
  first = pre;
}

StrStrPair::~StrStrPair() = default;

void StrStrPair::print(std::ostream &ost)
{
  ost << first << " " << second;
}

int operator==(const StrStrPair &left, const StrStrPair &right)
{
  return (right.first == left.first && right.second == left.second);
}

// String String Integer Pair
StrStrIntPair::StrStrIntPair(const char *pgName, const char *libName, int c)
{
  first  = pgName;
  second = libName;
  code   = c;
}

StrStrIntPair::~StrStrIntPair() = default;

int operator==(const StrStrIntPair &left, const StrStrIntPair &right)
{
  return (right.first == left.first && right.second == left.second);
}

