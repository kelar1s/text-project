#include <iostream>
#include "TextDocument.hpp"
#include "Part.hpp"
#include "Chapter.hpp"
#include "Section.hpp"
#include "Paragraph.hpp"
#include "Sentence.hpp"

int main()
{
    ITextNode *doc = new TextDocument("DOCC");

    doc->addChild(new Part("PART1"));

    ITextNode *part1 = doc->getChild(0);
    if (part1)
    {
        part1->addChild(new Chapter("CHAPTER1"));

        ITextNode *ch1 = part1->getChild(0);
        if (ch1)
        {
            ch1->addChild(new Section("SECTION1"));
            ITextNode *s1_1 = ch1->getChild(0);

            s1_1->addChild(new Paragraph("PARAGRAPH1"));
            s1_1->getChild(0)->addChild(new Sentence("SENTENCE1"));
            s1_1->getChild(0)->addChild(new Sentence("SENTENCE2"));

            s1_1->addChild(new Paragraph("PARAGRAPH2"));
            s1_1->getChild(1)->addChild(new Sentence("SENTENCE1"));
        }
    }

    doc->addChild(new Part("PART2"));
    ITextNode *part2 = doc->getChild(1);
    if (part2)
    {
        part2->addChild(new Chapter("CHAPTER2"));
        part2->getChild(0)->addChild(new Paragraph("PARAGRAPH1"));
        part2->getChild(0)->getChild(0)->addChild(new Sentence("SENTENCE1"));
    }

    std::cout << " - Содержимое - " << std::endl;
    std::cout << doc->toString() << std::endl;

    std::cout << " - Удаляем PART2" << std::endl;
    doc->removeChild(1);

    std::cout << " - Послу удаления - " << std::endl;
    std::cout << doc->toString() << std::endl;

    delete doc;

    return 0;
}