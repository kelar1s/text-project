#pragma once
#include "TextNodeBase.hpp"

class Section : public TextNodeBase
{
public:
   Section(const std::string &title = "Section") : TextNodeBase(title) {}
};