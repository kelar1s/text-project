#pragma once

#include "TextNodeBase.hpp"

class Sentence : public TextNodeBase
{
public:
   Sentence(const std::string &str = "Sentence") : TextNodeBase(str) {}

   void addChild(ITextNode *child) override
   {
      throw -1;
   }

   void removeChild(size_t index) override
   {
      throw -1;
   }

   ITextNode *getChild(size_t index) override
   {
      return nullptr;
   }

   size_t childCount() const override
   {
      return 0;
   }

   std::string toString(size_t indent = 0) const override
   {
      std::string result(indent, ' ');
      result += "- " + title + "\n";
      return result;
   }
};