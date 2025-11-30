#pragma once
#include <string>

class TextNode
{
   std::string text;

public:
   TextNode *pNext;
   TextNode *pDown;

   TextNode(const std::string &_text = "");
   ~TextNode();

   const std::string getText() const;
   void setText(const std::string &_text);

   void addNext(TextNode *node);
   void addDown(TextNode *node);

   std::string toString(size_t indent = 0) const;
};