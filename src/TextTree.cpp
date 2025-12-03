#include "TextTree.hpp"

TextTree::~TextTree()
{
   deleteTreeNode(pRoot);
}

void TextTree::deleteTreeNode(TextNode *tNode)
{
   if (tNode == nullptr)
   {
      return;
   }
   deleteTreeNode(tNode->pDown);
   deleteTreeNode(tNode->pNext);

   delete tNode;
}

TextNode *TextTree::setRoot(const std::string &_text)
{
   if (pRoot != nullptr)
   {
      deleteTreeNode(pRoot);
      pRoot = nullptr;
   }
   pRoot = new TextNode(_text);
   return pRoot;
}

TextNode *TextTree::addNext(TextNode *parent, const std::string &_text)
{
   if (parent == nullptr)
   {
      throw -1;
   }

   TextNode *current = parent;
   while (current->pNext != nullptr)
   {
      current = current->pNext;
   }
   current->pNext = new TextNode(_text);
   return current->pNext;
}

TextNode *TextTree::addDown(TextNode *parent, const std::string &_text)
{
   if (parent == nullptr)
   {
      throw -1;
   }
   if (parent->pDown == nullptr)
   {
      return parent->pDown = new TextNode(_text);
   }
   TextNode *current = parent->pDown;

   while (current->pNext != nullptr)
   {
      current = current->pNext;
   }
   return current->pNext = new TextNode(_text);
}

TextIterator TextTree::begin()
{
   return TextIterator(pRoot);
}

TextIterator TextTree::end()
{
   return TextIterator(nullptr);
}

std::string TextTree::toString() const
{
   return recursivePrint(pRoot, 0);
}

std::string TextTree::recursivePrint(const TextNode *tNode, size_t indent) const
{
   if (tNode == nullptr)
   {
      return "";
   }

   std::string res(indent, ' ');
   res += "- " + tNode->text + "\n";

   if (tNode->pDown)
   {
      res += recursivePrint(tNode->pDown, indent + 2);
   }

   if (tNode->pNext)
   {
      res += recursivePrint(tNode->pNext, indent);
   }

   return res;
}