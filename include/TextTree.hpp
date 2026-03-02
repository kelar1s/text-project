#include <string>

#include "TextIterator.hpp"
#include "TextNode.hpp"

class TextTree {
   TextNode* pRoot;

   void removeNodeWithAllDependencies(TextNode* tNode);
   std::string recursivePrint(const TextNode* tNode, size_t indent) const;

   TextNode** findPointerTo(TextNode** currNode, TextNode* targetNode);
   TextNode* findPredecessor(TextNode* currNode, TextNode* targetNode);
   TextNode* findParent(TextNode* currNode, TextNode* targetNode);

  public:
   TextTree() : pRoot(nullptr) {}
   ~TextTree();

   TextNode* setRoot(const std::string& _text);

   TextNode* addNextBack(TextNode* parent, const std::string& _text);
   TextNode* addDownBack(TextNode* parent, const std::string& _text);
   TextNode* addNextFront(TextNode* parent, const std::string& _text);
   TextNode* addDownFront(TextNode* parent, const std::string& _text);
   TextNode* addSplit(TextNode* tNode, const std::string& _text);

   void removeSubtree(TextNode* targetNode);
   void removeNodeUpChildren(TextNode* targetNode);
   void removeNodeAdoptChildren(TextNode* targetNode);

   TextIterator begin();
   TextIterator end();

   std::string toString() const;
};