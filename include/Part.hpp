#pragma once
#include "TextNodeBase.hpp"

class Part : public TextNodeBase
{
public:
   Part(const std::string &title = "Part") : TextNodeBase(title) {}
};