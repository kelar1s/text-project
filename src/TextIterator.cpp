#include "TextIterator.hpp"
#include "TextNode.hpp"

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
