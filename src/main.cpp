#include "TextTree.hpp"
#include <iostream>

int main()
{
   TextTree document;

   TextNode *root = document.setRoot("Document 1");

   TextNode *part1 = document.addDown(root, "Part 1");
   TextNode *part2 = document.addNext(part1, "Part 2");

   TextNode *chapter11 = document.addDown(part1, "Chapter 1.1");
   TextNode *chapter12 = document.addNext(chapter11, "Chapter 1.2");

   TextNode *chapter21 = document.addDown(part2, "Chapter 2.1");

   TextNode *s1 = document.addDown(chapter11, "Sentence 1");
   TextNode *s2 = document.addDown(chapter12, "Sentence 2");
   TextNode *s3 = document.addDown(chapter21, "Sentence 3");

   // std::cout << document.toString() << std::endl;
   for (TextIterator i = document.begin(); i != document.end(); ++i)
   {
      std::cout << i->getText() << std::endl;
   }
   return 0;
}