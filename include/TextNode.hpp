#pragma once
#include <string>
#include "TextIterator.hpp"

class TextNode
{
   friend class TextTree;
   friend class TextIterator;

   std::string text;
   TextNode *pNext;
   TextNode *pDown;

   TextNode(const std::string &_text = "") : text(_text), pNext(nullptr), pDown(nullptr) {}

public:
   const std::string &getText() const { return text; }
   void setText(const std::string &_text = "")
   {
      text = _text;
   }
};