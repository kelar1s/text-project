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
      throw InvalidNodeException("targetNode is nullptr.");
   }
   TextNode** pointerToTarget = findPointerTo(&pRoot, targetNode);
   if (pointerToTarget == nullptr) {
      throw NodeNotFoundException();
   }
   *pointerToTarget = targetNode->pNext;
   targetNode->pNext = nullptr;

   removeNodeWithAllDependencies(targetNode);
}

void TextTree::removeNodeUpChildren(TextNode* targetNode) {
   if (targetNode == nullptr) {
      throw InvalidNodeException("Node is nullptr.");
   }
   if(targetNode == pRoot){
      InvalidNodeException("Cannot remove pRoot with level up.");
   }
   TextNode** pointerToTarget = findPointerTo(&pRoot, targetNode);
   if (pointerToTarget == nullptr) {
      throw NodeNotFoundException();
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
   if (targetNode == nullptr) {
      throw InvalidNodeException("Node is nullptr.");
   }

   if(targetNode == pRoot){
      InvalidNodeException("Cannot remove pRoot with adopting.");
   }

   TextNode* predNode = findPredecessor(pRoot, targetNode);
   if (predNode == nullptr) {
      throw NodeNotFoundException();
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
   if (currNode == nullptr) {
      throw InvalidNodeException("Node is nullptr.");
   }

   if(currNode == pRoot){
      InvalidNodeException("Node cannot be pRoot.");
   }

   TextNode* parent = findParent(pRoot, currNode);
   if (parent == nullptr) {
      throw NodeNotFoundException();
   }
   if (parent == pRoot) {
      throw InvalidNodeException("Node cannot be 1 level lower than the pRoot.");
   }
   TextNode* newNode = new TextNode(_text);

   newNode->pDown = currNode->pNext;
   currNode->pNext = nullptr;

   newNode->pNext = parent->pNext;
   parent->pNext = newNode;

   return newNode;
}

TextNode* TextTree::addNextAfter(TextNode* currNode, const std::string& _text) {
   if (currNode == nullptr) {
      throw InvalidNodeException("Node is nullptr.");
   }
   if (currNode == pRoot) {
      throw InvalidNodeException("Node cannot be pRoot.");
   }
   TextNode* prevNode = currNode->pNext;

   TextNode* newNode = new TextNode(_text);

   newNode->pNext = prevNode;
   currNode->pNext = newNode;

   return newNode;
}

TextNode* TextTree::addNextBefore(TextNode* currNode,
                                  const std::string& _text) {
   if (currNode == nullptr) {
      throw InvalidNodeException("Node is nullptr.");
   }
   if (currNode == pRoot) {
      throw InvalidNodeException("Node cannot be pRoot.");
   }
   TextNode** ptrToCurrNode = findPointerTo(&pRoot, currNode);
   if (ptrToCurrNode == nullptr) {
      throw NodeNotFoundException();
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
   if (currNode == nullptr) {
      throw InvalidNodeException("Node is nullptr.");
   }
   if (currNode == pRoot) {
      throw InvalidNodeException("Cannot raise pRoot level.");
   }

   TextNode** ptrToCurrNode = findPointerTo(&pRoot, currNode);
   if (ptrToCurrNode == nullptr) {
      throw NodeNotFoundException();
   }
   TextNode* parent = findParent(pRoot, currNode);
   if (parent == nullptr) {
      throw NodeNotFoundException();
   }
   if (parent == pRoot) {
      throw InvalidNodeException("Node cannot be 1 level lower than the pRoot.");
   }

   *ptrToCurrNode = nullptr;
   
   if(currNode->pDown == nullptr){
      currNode->pDown = currNode->pNext;
   } else {
      TextNode *child = currNode->pDown;
      while(child->pNext != nullptr){
         child = child->pNext;
      }
      child->pNext = currNode->pNext;
   }

   currNode->pNext = parent->pNext;
   parent->pNext = currNode;

   return currNode;
}

TextNode* TextTree::lowerLevel(TextNode* currNode) {
   if (currNode == nullptr) {
      throw InvalidNodeException("Node is nullptr.");
   }
   if (currNode == pRoot) {
      throw InvalidNodeException("Cannot lower pRoot level.");
   }

   TextNode* predNode = findPredecessor(pRoot, currNode);
   if (predNode == nullptr) {
      throw NodeNotFoundException();
   }
   if (predNode == pRoot) {
      throw InvalidNodeException("Node cannot be level lower.");
   }
   if (predNode->pDown == currNode) {
      throw InvalidNodeException("Node cannot be level lower.");
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
