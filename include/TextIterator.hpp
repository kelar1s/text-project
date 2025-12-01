#pragma once
#include <stack>

class TextNode;

class TextIterator
{
   TextNode *pCurr;
   std::stack<TextNode *> stack;

public:
   TextIterator(TextNode *root = nullptr) : pCurr(root) {}
   TextIterator(const TextIterator &ti) : pCurr(ti.pCurr), stack(ti.stack) {}

   bool operator==(const TextIterator &oth) const
   {
      return this->pCurr == oth.pCurr;
   }

   bool operator!=(const TextIterator &oth) const
   {
      return this->pCurr != oth.pCurr;
   }

   TextNode &operator*() const
   {
      return *pCurr;
   }

   TextNode *operator->() const
   {
      return pCurr;
   }

   TextIterator &operator++();
};