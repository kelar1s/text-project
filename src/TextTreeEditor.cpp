#include "TextTreeEditor.hpp"

#include <iostream>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

const std::string COLOR_GREEN = "\033[32m";
const std::string COLOR_RESET = "\033[0m";

TextTreeEditor::TextTreeEditor() : selectedIndex(0), lastMessage("") {
    tree.setRoot("pRoot: Document");

}

void TextTreeEditor::run()
{
   bool isRunning = true;
    while (isRunning) {
        std::vector<TextNode*> displayList;
        TreeToList(tree.getRoot(), displayList);
        
        drawInterface(displayList);
        
        int key = getKeystroke();
        isRunning = processInput(key, displayList);
    }
}

void TextTreeEditor::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int TextTreeEditor::getKeystroke() const {
#ifdef _WIN32
    int ch = _getch();
    if (ch == 0 || ch == 224) {
        ch = _getch();
        if (ch == 72) return 1000;
        if (ch == 80) return 1001;
    }
    return ch;
#else
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    if (ch == 27) {
      int next1 = getchar();
      int next2 = getchar();
      if (next1 == '[' && next2 == 'A')
        ch = 1000;  
      else if (next1 == '[' && next2 == 'B')
        ch = 1001;
      else
        ch = 27;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}

void TextTreeEditor::TreeToList(TextNode *node, std::vector<TextNode *> &list) const
{
   if (node == nullptr) return;
    list.push_back(node);
    TreeToList(node->getDown(), list);
    TreeToList(node->getNext(), list);
}

void TextTreeEditor::PrintTree(TextNode *currNode, size_t indent, TextNode *selectedNode) const
{
   if (currNode == nullptr) return;

    std::string indentStr(indent, ' ');
    std::cout << indentStr << "- ";
    
    if (currNode == selectedNode) {
        std::cout << COLOR_GREEN << currNode->getText() << " <--" << COLOR_RESET << "\n";
    } else {
        std::cout << currNode->getText() << "\n";
    }

    PrintTree(currNode->getDown(), indent + 2, selectedNode);
    PrintTree(currNode->getNext(), indent, selectedNode);
}

std::string TextTreeEditor::promptForText(const std::string &prompt) const
{
   std::cout << prompt;
   std::string text;
   std::getline(std::cin, text);
   return text;
}

void TextTreeEditor::drawInterface(const std::vector<TextNode *> &displayList)
{
   clearScreen();
    
    if (displayList.empty()) {
        std::cout << "Tree is empty.\n";
        selectedIndex = 0;
    } else {
        if (selectedIndex >= displayList.size()) {
            selectedIndex = displayList.size() - 1;
        }
        TextNode* selectedNode = displayList[selectedIndex];
        
        std::cout << "=== TEXT TREE ===\n";
        PrintTree(displayList[0], 0, selectedNode);
    }

    std::cout << "\n----------------------------------------\n";
    std::cout << "Operations:\n";
    std::cout << "1. addDownAfter      7. removeSubtree\n";
    std::cout << "2. addNextAfter      8. removeNodeUpChildren\n";
    std::cout << "3. addNextBefore     9. removeNodeAdoptChildren\n";
    std::cout << "4. addSplit          p. setRoot\n";
    std::cout << "5. raiseLevel        u. setText\n";
    std::cout << "6. lowerLevel        q. Exit\n";
    std::cout << "\nMessage: " << lastMessage << "\n";
    std::cout << "Select action: ";
}

bool TextTreeEditor::processInput(int key, std::vector<TextNode *> &displayList)
{
   TextNode* targetNode = displayList.empty() ? nullptr : displayList[selectedIndex];
    lastMessage = "";

    try {
        if (key == 1000 || key == 'w' || key == 'W') { 
            if (selectedIndex > 0) selectedIndex--;
        } 
        else if (key == 1001 || key == 's' || key == 'S') { 
            if (selectedIndex < displayList.size() - 1) selectedIndex++;
        } 
        else if (key == 'q') {
            return false;
        } 
        else if (key >= '1' && key <= '4') {
            if (!targetNode) throw std::runtime_error("No node selected!");
            std::cout << "\n";
            std::string text = promptForText("Enter text for new node: ");
            
            if (key == '1') tree.addDownAfter(targetNode, text);
            if (key == '2') tree.addNextAfter(targetNode, text);
            if (key == '3') tree.addNextBefore(targetNode, text);
            if (key == '4') tree.addSplit(targetNode, text);
            
            lastMessage = "Node added successfully.";
        } 
        else if (key >= '5' && key <= '9') {
            if (!targetNode) throw std::runtime_error("No node selected!");
            
            if (key == '5') tree.raiseLevel(targetNode);
            if (key == '6') tree.lowerLevel(targetNode);
            if (key == '7') tree.removeSubtree(targetNode);
            if (key == '8') tree.removeNodeUpChildren(targetNode);
            if (key == '9') tree.removeNodeAdoptChildren(targetNode);
            
            lastMessage = "Operation completed successfully.";
        } 
        else if (key == 'u' || key == 'p') {
            if (!targetNode) throw std::runtime_error("No node selected!");
            std::cout << "\n";
            std::string text = promptForText("Enter text for new node: ");

            if (key == 'u') targetNode->setText(text);
            if (key == 'p') tree.setRoot(text);

            lastMessage = "Node updated successfully.";
        }
        else {
            lastMessage = "Unknown key pressed. Code: " + std::to_string(key);
        }
    } 
    catch (const std::exception& e) {
        lastMessage = e.what();
    } 
    catch (...) {
        lastMessage = "UNKNOWN ERROR";
    }
    
    return true;
}
