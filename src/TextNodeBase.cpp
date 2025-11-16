#include "TextNodeBase.hpp"

TextNodeBase::TextNodeBase(const std::string &str) : title(str) {}

TextNodeBase::~TextNodeBase()
{
   for (ITextNode *child : children)
   {
      delete child;
   }
}

void TextNodeBase::addChild(ITextNode *child)
{
   if (child == nullptr)
   {
      throw -1;
   }
   children.push_back(child);
}

void TextNodeBase::removeChild(size_t index)
{
   if (index < 0 || index >= children.size())
   {
      throw -1;
   }
   delete children[index];
   children.erase(children.begin() + index);
}

ITextNode *TextNodeBase::getChild(size_t index)
{
   if (index < 0 || index >= children.size())
   {
      throw -1;
   }
   return children[index];
}

size_t TextNodeBase::childCount() const
{
   return children.size();
}

void TextNodeBase::setTitle(const std::string &str)
{
   title = str;
}

const std::string TextNodeBase::getTitle()
{
   return title;
}

std::string TextNodeBase::toString(size_t indent) const
{
   std::string result(indent, ' ');
   result += "+ " + title + "\n";

   for (const ITextNode *child : children)
   {
      if (child)
      {
         result += child->toString(indent + 2);
      }
   }
   return result;
}