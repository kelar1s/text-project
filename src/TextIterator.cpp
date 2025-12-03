#include "TextIterator.hpp"
#include "TextNode.hpp"

bool TextIterator::operator==(const TextIterator &oth) const
{
   return pCurr == oth.pCurr;
}
bool TextIterator::operator!=(const TextIterator &oth) const
{
   return pCurr != oth.pCurr;
}

TextNode &TextIterator::operator*() const
{
   return *pCurr;
}
TextNode *TextIterator::operator->() const
{
   return pCurr;
}

TextIterator &TextIterator::operator++()
{
   if (pCurr == nullptr)
   {
      return *this;
   }

   if (pCurr->pDown != nullptr)
   {
      if (pCurr->pNext != nullptr)
      {
         stack.push(pCurr->pNext);
      }
      pCurr = pCurr->pDown;
      return *this;
   }

   if (pCurr->pNext != nullptr)
   {
      pCurr = pCurr->pNext;
      return *this;
   }

   if (!stack.empty())
   {
      pCurr = stack.top();
      stack.pop();
      return *this;
   }

   pCurr = nullptr;
   return *this;
}
