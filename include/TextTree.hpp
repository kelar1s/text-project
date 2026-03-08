#include <string>

#include "TextIterator.hpp"
#include "TextNode.hpp"

class TextTree {
   TextNode* pRoot;

   void removeNodeWithAllDependencies(TextNode* currNode);
   std::string recursivePrint(const TextNode* currNode, size_t indent) const;

   TextNode** findPointerTo(TextNode** currNode, TextNode* targetNode);
   TextNode* findPredecessor(TextNode* currNode, TextNode* targetNode);
   TextNode* findParent(TextNode* currNode, TextNode* targetNode);

  public:
   TextTree();
   ~TextTree();

   TextNode* setRoot(const std::string& _text);

   TextNode* addNextAfter(TextNode* currNode, const std::string& _text);
   TextNode* addNextBefore(TextNode* currNode, const std::string& _text);
   TextNode* addDownAfter(TextNode* currNode, const std::string& _text);
   TextNode* addSplit(TextNode* currNode, const std::string& _text);

   void removeSubtree(TextNode* targetNode);
   void removeNodeUpChildren(TextNode* targetNode);
   void removeNodeAdoptChildren(TextNode* targetNode);

   TextNode* raiseLevel(TextNode* currNode);

   TextIterator begin();
   TextIterator end();

   std::string toString() const;
};