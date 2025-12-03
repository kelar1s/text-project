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

   bool operator==(const TextIterator &oth) const;
   bool operator!=(const TextIterator &oth) const;

   TextNode &operator*() const;
   TextNode *operator->() const;

   TextIterator &operator++();
};