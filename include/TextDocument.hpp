#pragma once
#include "TextNodeBase.hpp"

class TextDocument : public TextNodeBase
{
public:
   TextDocument(const std::string &title = "Document") : TextNodeBase(title) {}
};