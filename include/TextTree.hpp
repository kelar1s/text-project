#include "TextNode.hpp"
#include "TextIterator.hpp"

class TextTree
{
   TextNode *pRoot;

   void deleteTreeNode(TextNode *tNode);
   std::string recursivePrint(const TextNode *tNode, size_t indent) const;

public:
   TextTree() : pRoot(nullptr) {}
   ~TextTree();

   TextNode *setRoot(const std::string &_text);

   TextNode *addNext(TextNode *parent, const std::string &_text);
   TextNode *addDown(TextNode *parent, const std::string &_text);

   TextIterator begin();
   TextIterator end();

   std::string toString() const;
};