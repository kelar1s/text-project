#pragma once
#include "TextNodeBase.hpp"

class Chapter : public TextNodeBase
{
public:
   Chapter(const std::string &title = "Chapter") : TextNodeBase(title) {}
};