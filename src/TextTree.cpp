#include "TextTree.hpp"

#include <string>

TextTree::~TextTree() { removeNodeWithAllDependencies(pRoot); }

void TextTree::removeNodeWithAllDependencies(TextNode* tNode) {
   if (tNode == nullptr) {
      return;
   }
   removeNodeWithAllDependencies(tNode->pDown);
   removeNodeWithAllDependencies(tNode->pNext);

   delete tNode;
}

TextNode* TextTree::setRoot(const std::string& _text) {
   if (pRoot != nullptr) {
      removeNodeWithAllDependencies(pRoot);
      pRoot = nullptr;
   }
   pRoot = new TextNode(_text);
   return pRoot;
}

TextNode* TextTree::addNextBack(TextNode* parent, const std::string& _text) {
   if (parent == nullptr || parent == pRoot) {
      throw -1;
   }

   TextNode* current = parent;
   while (current->pNext != nullptr) {
      current = current->pNext;
   }
   current->pNext = new TextNode(_text);
   return current->pNext;
}

TextNode* TextTree::addDownBack(TextNode* parent, const std::string& _text) {
   if (parent == nullptr) {
      throw -1;
   }
   if (parent->pDown == nullptr) {
      return parent->pDown = new TextNode(_text);
   }
   TextNode* current = parent->pDown;

   while (current->pNext != nullptr) {
      current = current->pNext;
   }
   return current->pNext = new TextNode(_text);
}

TextIterator TextTree::begin() { return TextIterator(pRoot); }

TextIterator TextTree::end() { return TextIterator(nullptr); }

std::string TextTree::toString() const { return recursivePrint(pRoot, 0); }

std::string TextTree::recursivePrint(const TextNode* tNode,
                                     size_t indent) const {
   if (tNode == nullptr) {
      return "";
   }

   std::string res = "";
   res.append(indent, ' ');
   res += "- ";
   res += tNode->text + "\n";

   if (tNode->pDown) {
      res += recursivePrint(tNode->pDown, indent + 2);
   }

   if (tNode->pNext) {
      res += recursivePrint(tNode->pNext, indent);
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

TextNode* TextTree::addSplit(TextNode* tNode, const std::string& _text) {
   if (tNode == nullptr || tNode == pRoot) {
      throw -1;
   }
   TextNode* parent = findParent(pRoot, tNode);
   if (parent == nullptr) {
      throw -1;
   }
   TextNode* newNode = new TextNode(_text);

   newNode->pDown = tNode->pNext;
   tNode->pNext = nullptr;

   newNode->pNext = parent->pNext;
   parent->pNext = newNode;

   return newNode;
}

TextNode* TextTree::addNextFront(TextNode* parent, const std::string& _text) {
   TextNode* prevNode = parent->pNext;

   TextNode* newNode = new TextNode(_text);

   newNode->pNext = prevNode;
   parent->pNext = newNode;

   return newNode;
}

TextNode* TextTree::addDownFront(TextNode* parent, const std::string& _text) {
   TextNode* prevNode = parent->pDown;

   TextNode* newNode = new TextNode(_text);

   newNode->pNext = prevNode;
   parent->pDown = newNode;

   return newNode;
}