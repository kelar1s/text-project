#pragma once
#include "TextNodeBase.hpp"

class Paragraph : public TextNodeBase
{
public:
   Paragraph(const std::string &title = "Paragraph") : TextNodeBase(title) {}
};