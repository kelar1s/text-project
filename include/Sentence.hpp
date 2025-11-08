#pragma once

#include "TextNodeBase.hpp"

class Sentence : public TextNodeBase
{
public:
   Sentence(const std::string &str) : TextNodeBase(str) {}

   void addChild(ITextNode *child) override
   {
      delete child;
   }

   void removeChild(size_t index) override
   {
   }

   ITextNode *getChild(size_t index) override
   {
      return nullptr;
   }

   std::string toString(size_t indent = 0) const override
   {
      std::string result(indent, ' ');
      result += "- " + title + "\n";
      return result;
   }
};