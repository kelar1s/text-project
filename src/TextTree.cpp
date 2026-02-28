#include "TextTree.hpp"

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

TextNode* TextTree::addNext(TextNode* parent, const std::string& _text) {
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

TextNode* TextTree::addDown(TextNode* parent, const std::string& _text) {
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

   std::string res(indent, ' ');
   res += "- " + tNode->text + "\n";

   if (tNode->pDown) {
      res += recursivePrint(tNode->pDown, indent + 2);
   }

   if (tNode->pNext) {
      res += recursivePrint(tNode->pNext, indent);
   }

   return res;
}

TextNode** TextTree::findPointerTo(TextNode** currNode, TextNode* targetNode) {
   if (currNode == nullptr) {
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
      TextNode* targetNodeChild = targetNode->pDown;
      while (targetNodeChild->pNext != nullptr) {
         targetNodeChild = targetNodeChild->pNext;
      }
      *pointerToTarget = targetNode->pDown;
      targetNodeChild->pNext = targetNode->pNext;
   }
   targetNode->pDown = nullptr;
   targetNode->pNext = nullptr;
   delete targetNode;
}

TextNode* TextTree::findpPredecessor(TextNode* currNode, TextNode* targetNode) {
   if (!currNode || !targetNode || currNode == targetNode) return nullptr;

   if (currNode->pDown == targetNode) return currNode;
   if (currNode->pNext == targetNode) return currNode;

   TextNode* res = findpPredecessor(currNode->pDown, targetNode);
   if (res) return res;

   return findpPredecessor(currNode->pNext, targetNode);
}

void TextTree::removeNodeAdoptChildren(TextNode* targetNode) {
   if (targetNode == nullptr || targetNode == pRoot) {
      throw -1;
   }
   TextNode** pointerToTarget = findPointerTo(&pRoot, targetNode);
   if (pointerToTarget == nullptr) {
      throw -1;
   }
   TextNode* predNode = findpPredecessor(pRoot, targetNode);
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
