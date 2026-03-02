#include <iostream>

#include "TextTree.hpp"

int main() {
   TextTree document;

   TextNode* root = document.setRoot("Document 1");

   TextNode* part1 = document.addDownBack(root, "Part 1");

   TextNode* part2 = document.addNextBack(part1, "Part 2");

   TextNode* chapter11 = document.addDownBack(part1, "Chapter 1.1");

   TextNode* chapter12 = document.addNextBack(chapter11, "Chapter 1.2");

   TextNode* chapter21 = document.addDownBack(part2, "Chapter 2.1");

   TextNode* s1 = document.addDownBack(chapter11, "Sentence 1");

   TextNode* s2 = document.addDownBack(chapter12, "Sentence 2");

   TextNode* s3 = document.addDownBack(chapter21, "Sentence 3");

   std::cout << document.toString() << std::endl;

   // for (TextIterator i = document.begin(); i != document.end(); ++i) {

   // std::cout << i->getText() << std::endl;

   // }

   std::cout << "---------After----------\n";

   document.removeSubtree(chapter21);

   std::cout << document.toString() << std::endl;

   return 0;
}