#include "TextTree.hpp"

#include <string>

TextTree::TextTree() : pRoot(nullptr) {}

TextTree::~TextTree() { removeNodeWithAllDependencies(pRoot); }

void TextTree::removeNodeWithAllDependencies(TextNode* currNode) {
   if (currNode == nullptr) {
      return;
   }
   removeNodeWithAllDependencies(currNode->pDown);
   removeNodeWithAllDependencies(currNode->pNext);

   delete currNode;
}

TextNode* TextTree::setRoot(const std::string& _text) {
   if (pRoot != nullptr) {
      removeNodeWithAllDependencies(pRoot);
      pRoot = nullptr;
   }
   pRoot = new TextNode(_text);
   return pRoot;
}

TextIterator TextTree::begin() { return TextIterator(pRoot); }

TextIterator TextTree::end() { return TextIterator(nullptr); }

std::string TextTree::toString() const { return recursivePrint(pRoot, 0); }

std::string TextTree::recursivePrint(const TextNode* currNode,
                                     size_t indent) const {
   if (currNode == nullptr) {
      return "";
   }

   std::string res = "";
   res.append(indent, ' ');
   res += "- ";
   res += currNode->text + "\n";

   if (currNode->pDown) {
      res += recursivePrint(currNode->pDown, indent + 2);
   }

   if (currNode->pNext) {
      res += recursivePrint(currNode->pNext, indent);
   }

   return res;
}

TextNode** TextTree::findPointerTo(TextNode** currNode, TextNode* targetNode) {
   if (currNode == nullptr || *currNode == nullptr) {
      return nullptr;
   }
   if (*currNode == targetNode) {
      return currNode;
   }
   TextNode** downRes = findPointerTo(&((*currNode)->pDown), targetNode);
   if (downRes != nullptr) {
      return downRes;
   }
   TextNode** nextRes = findPointerTo(&((*currNode)->pNext), targetNode);
   if (nextRes != nullptr) {
      return nextRes;
   }
   return nullptr;
}

void TextTree::removeSubtree(TextNode* targetNode) {
   if (targetNode == nullptr) {
      throw -1;
   }
   TextNode** pointerToTarget = findPointerTo(&pRoot, targetNode);
   if (pointerToTarget == nullptr) {
      throw -1;
   }
   *pointerToTarget = targetNode->pNext;
   targetNode->pNext = nullptr;

   removeNodeWithAllDependencies(targetNode);
}

void TextTree::removeNodeUpChildren(TextNode* targetNode) {
   if (targetNode == nullptr || targetNode == pRoot) {
      throw -1;
   }
   TextNode** pointerToTarget = findPointerTo(&pRoot, targetNode);
   if (pointerToTarget == nullptr) {
      throw -1;
   }
   if (targetNode->pDown == nullptr) {
      *pointerToTarget = targetNode->pNext;
   } else {
      TextNode* lastChild = targetNode->pDown;
      while (lastChild->pNext != nullptr) {
         lastChild = lastChild->pNext;
      }
      *pointerToTarget = targetNode->pDown;
      lastChild->pNext = targetNode->pNext;
   }
   targetNode->pDown = nullptr;
   targetNode->pNext = nullptr;
   delete targetNode;
}

TextNode* TextTree::findPredecessor(TextNode* currNode, TextNode* targetNode) {
   if (!currNode || !targetNode || currNode == targetNode) return nullptr;

   if (currNode->pDown == targetNode) return currNode;
   if (currNode->pNext == targetNode) return currNode;

   TextNode* res = findPredecessor(currNode->pDown, targetNode);
   if (res) return res;

   return findPredecessor(currNode->pNext, targetNode);
}

void TextTree::removeNodeAdoptChildren(TextNode* targetNode) {
   if (targetNode == nullptr || targetNode == pRoot) {
      throw -1;
   }
   TextNode* predNode = findPredecessor(pRoot, targetNode);
   if (predNode == nullptr) {
      throw -1;
   }
   if (predNode->pNext == targetNode) {
      if (targetNode->pDown != nullptr) {
         if (predNode->pDown == nullptr) {
            predNode->pDown = targetNode->pDown;
         } else {
            TextNode* lastChild = predNode->pDown;
            while (lastChild->pNext != nullptr) {
               lastChild = lastChild->pNext;
            }
            lastChild->pNext = targetNode->pDown;
         }
      }
      predNode->pNext = targetNode->pNext;
   } else {
      removeNodeUpChildren(targetNode);
      return;
   }
   targetNode->pNext = nullptr;
   targetNode->pDown = nullptr;
   delete targetNode;
}

TextNode* TextTree::findParent(TextNode* currNode, TextNode* targetNode) {
   if (currNode == nullptr || targetNode == nullptr) {
      return nullptr;
   }
   TextNode* child = currNode->pDown;
   while (child) {
      if (child == targetNode) {
         return currNode;
      }
      child = child->pNext;
   }
   TextNode* res = findParent(currNode->pDown, targetNode);
   if (res != nullptr) {
      return res;
   }
   return findParent(currNode->pNext, targetNode);
}

TextNode* TextTree::addSplit(TextNode* currNode, const std::string& _text) {
   if (currNode == nullptr || currNode == pRoot) {
      throw -1;
   }
   TextNode* parent = findParent(pRoot, currNode);
   if (parent == nullptr || parent == pRoot) {
      throw -1;
   }
   TextNode* newNode = new TextNode(_text);

   newNode->pDown = currNode->pNext;
   currNode->pNext = nullptr;

   newNode->pNext = parent->pNext;
   parent->pNext = newNode;

   return newNode;
}

TextNode* TextTree::addNextAfter(TextNode* currNode, const std::string& _text) {
   TextNode* prevNode = currNode->pNext;

   TextNode* newNode = new TextNode(_text);

   newNode->pNext = prevNode;
   currNode->pNext = newNode;

   return newNode;
}

TextNode* TextTree::addNextBefore(TextNode* currNode,
                                  const std::string& _text) {
   if (currNode == nullptr || currNode == pRoot) {
      throw -1;
   }
   TextNode** ptrToCurrNode = findPointerTo(&pRoot, currNode);
   if (ptrToCurrNode == nullptr) {
      throw -1;
   }

   TextNode* newNode = new TextNode(_text);
   newNode->pNext = *ptrToCurrNode;
   *ptrToCurrNode = newNode;

   return newNode;
}

TextNode* TextTree::addDownAfter(TextNode* currNode, const std::string& _text) {
   TextNode* prevNode = currNode->pDown;

   TextNode* newNode = new TextNode(_text);

   newNode->pNext = prevNode;
   currNode->pDown = newNode;

   return newNode;
}

TextNode* TextTree::raiseLevel(TextNode* currNode) {
   if (currNode == nullptr || currNode == pRoot) {
      throw -1;
   }

   if (currNode->pDown != nullptr) {  // ! Question on next meetup
      throw -1;
   }

   TextNode** ptrToCurrNode = findPointerTo(&pRoot, currNode);
   if (ptrToCurrNode == nullptr) {
      throw -1;
   }
   TextNode* parent = findParent(pRoot, currNode);
   if (parent == pRoot || parent == nullptr) {  // ! TODO: split with exceptions
      throw -1;
   }
   *ptrToCurrNode = nullptr;
   parent->pNext = currNode;
   
   currNode->pDown = currNode->pNext;
   currNode->pNext = nullptr;

   return currNode;
}

TextNode* TextTree::lowerLevel(TextNode* currNode) {
   if (currNode == nullptr || currNode == pRoot) {
      throw -1;
   }

   TextNode* predNode = findPredecessor(pRoot, currNode);
   if (predNode == nullptr) {
      throw -1;
   }
   if (predNode->pDown == currNode) {
      return currNode;  // ? throw
   }

   predNode->pNext = currNode->pNext;

   if (predNode->pDown == nullptr) {
      predNode->pDown = currNode;
   } else {
      TextNode* child = predNode->pDown;
      while (child->pNext != nullptr) {
         child = child->pNext;
      }
      child->pNext = currNode;
   }
   currNode->pNext = currNode->pDown;
   currNode->pDown = nullptr;

   return currNode;
}
