#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include "TextTree.hpp"

class TextTreeEditor{
   TextTree tree;
   size_t selectedIndex;
   std::string lastMessage;
   void clearScreen() const;
    int getKeystroke() const;


    void TreeToList(TextNode* node, std::vector<TextNode*>& list) const;
    void PrintTree(TextNode* currNode, size_t indent, TextNode* selectedNode) const;
    std::string promptForText(const std::string& prompt) const;

    void drawInterface(const std::vector<TextNode*>& displayList);
    
    bool processInput(int key, std::vector<TextNode*>& displayList);

public:
    TextTreeEditor();
    void run();
};
