#include "TextNode.hpp"
#include <iostream>

int main()
{
   TextNode *doc = new TextNode("Документ");

   TextNode *chapter1 = new TextNode("Глава 1");
   TextNode *chapter2 = new TextNode("Глава 2");

   doc->addDown(chapter1);
   doc->addDown(chapter2);

   TextNode *section11 = new TextNode("Раздел 1.1");
   TextNode *section12 = new TextNode("Раздел 1.2");

   TextNode *section21 = new TextNode("Раздел 2.1");
   TextNode *section22 = new TextNode("Раздел 2.2");

   chapter1->addDown(section11);
   chapter1->addDown(section12);

   chapter2->addDown(section21);
   chapter2->addDown(section22);

   TextNode *p1 = new TextNode("Абзац 1.1");
   TextNode *p2 = new TextNode("Абзац 1.2");

   TextNode *p3 = new TextNode("Абзац 2.1");
   TextNode *p4 = new TextNode("Абзац 3.1");

   section11->addDown(p1);
   section11->addDown(p2);

   section21->addDown(p3);
   section21->addDown(p4);

   TextNode *s1 = new TextNode("Предложение 1");
   TextNode *s2 = new TextNode("Предложение 2");
   TextNode *s3 = new TextNode("Предложение 3");
   TextNode *s4 = new TextNode("Предложение 4");
   TextNode *s5 = new TextNode("Предложение 5");

   p1->addDown(s1);
   p1->addDown(s2);
   p1->addDown(s3);
   p3->addDown(s4);
   p4->addDown(s5);

   std::cout << doc->toString(0);

   // TextIterator ti(doc);

   // for (TextIterator ti = doc->begin(); ti != doc->end(); ++ti)
   // {
   //    std::cout << ti->getText() << "\n";
   // }

   delete doc;
   return 0;
}