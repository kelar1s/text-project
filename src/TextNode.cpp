#include "TextNode.hpp"

TextNode::TextNode(const std::string &_text)
{
   text = _text;
   pNext = nullptr;
   pDown = nullptr;
}

TextNode::~TextNode()
{
   delete pDown;
   delete pNext;
}

const std::string TextNode::getText() const
{
   return text;
}

void TextNode::setText(const std::string &_text)
{
   text = _text;
}

void TextNode::addNext(TextNode *node)
{
   if (node == nullptr)
   {
      throw -1;
   }
   TextNode *current = this;
   while (current->pNext != nullptr)
   {
      current = current->pNext;
   }
   current->pNext = node;
}

void TextNode::addDown(TextNode *node)
{
   if (node == nullptr)
   {
      throw -1;
   }
   if (this->pDown == nullptr)
   {
      this->pDown = node;
      return;
   }
   TextNode *current = this->pDown;
   while (current->pNext != nullptr)
   {
      current = current->pNext;
   }
   current->pNext = node;
}

std::string TextNode::toString(size_t indent) const
{
   std::string res(indent, ' ');
   res += "- " + text + "\n";
   if (pDown != nullptr)
   {
      res += pDown->toString(indent + 2);
   }
   if (pNext != nullptr)
   {
      res += pNext->toString(indent);
   }
   return res;
}