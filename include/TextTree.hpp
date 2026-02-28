#include "TextIterator.hpp"
#include "TextNode.hpp"

class TextTree {
   TextNode* pRoot;

   void removeNodeWithAllDependencies(TextNode* tNode);
   std::string recursivePrint(const TextNode* tNode, size_t indent) const;

   TextNode** findPointerTo(TextNode** currNode, TextNode* targetNode);
   TextNode* findpPredecessor(TextNode* currNode, TextNode* targetNode);

  public:
   TextTree() : pRoot(nullptr) {}
   ~TextTree();

   TextNode* setRoot(const std::string& _text);

   TextNode* addNext(TextNode* parent, const std::string& _text);
   TextNode* addDown(TextNode* parent, const std::string& _text);

   void removeSubtree(TextNode* targetNode);
   void removeNodeUpChildren(TextNode* targetNode);
   void removeNodeAdoptChildren(TextNode* targetNode);

   TextIterator begin();
   TextIterator end();

   std::string toString() const;
};