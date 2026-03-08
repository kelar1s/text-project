#include <iostream>

#include "TextTree.hpp"

int main() {
   TextTree document;

   TextNode* root = document.setRoot("Document 1");

   std::cout << document.toString() << std::endl;

   // for (TextIterator i = document.begin(); i != document.end(); ++i) {
   // std::cout << i->getText() << std::endl;
   // }

   return 0;
}