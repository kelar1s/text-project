#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "TextTree.hpp"

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
void clearScreen() { system("cls"); }
int getKeystroke() {
    int ch = _getch();
    if (ch == 0 || ch == 224) {
        ch = _getch();
        if (ch == 72) return 1000;
        if (ch == 80) return 1001;
    }
    return ch;
}
#else
#include <termios.h>
#include <unistd.h>
void clearScreen() { system("clear"); }
int getKeystroke() {
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
        if (next1 == '[' && next2 == 'A') ch = 1000;
        if (next1 == '[' && next2 == 'B') ch = 1001;
        else ch = 27;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

const std::string COLOR_GREEN = "\033[32m";
const std::string COLOR_RESET = "\033[0m";

void flattenTree(TextNode* node, std::vector<TextNode*>& list) {
    if (node == nullptr) return;
    list.push_back(node);
    flattenTree(node->getDown(), list);
    flattenTree(node->getNext(), list);
}

void printTreeInteractive(TextNode* currNode, size_t indent, TextNode* selectedNode) {
    if (currNode == nullptr) return;

    std::string indentStr(indent, ' ');
    std::cout << indentStr << "- ";
    
    if (currNode == selectedNode) {
        std::cout << COLOR_GREEN << currNode->getText() << " <--" << COLOR_RESET << "\n";
    } else {
        std::cout << currNode->getText() << "\n";
    }

    printTreeInteractive(currNode->getDown(), indent + 2, selectedNode);
    printTreeInteractive(currNode->getNext(), indent, selectedNode);
}

std::string promptForText(const std::string& prompt) {
    std::cout << prompt;
    std::string text;
    std::getline(std::cin, text);
    return text;
}

int main() {
    TextTree tree;
    tree.setRoot("pRoot: Document");

    size_t selectedIndex = 0;
    std::string lastMessage = "";

    while (true) {
        clearScreen();
        
        std::vector<TextNode*> displayList;
        flattenTree(tree.getRoot(), displayList);

        if (displayList.empty()) {
            std::cout << "Tree is empty.\n";
            selectedIndex = 0;
        } else {
            if (selectedIndex >= displayList.size()) {
                selectedIndex = displayList.size() - 1;
            }
            TextNode* selectedNode = displayList[selectedIndex];
            
            std::cout << "=== TEXT TREE ===\n";
            printTreeInteractive(displayList[0], 0, selectedNode);
        }

        std::cout << "\n----------------------------------------\n";
        std::cout << "Operations:\n";
        std::cout << "1. addDownAfter      7. removeSubtree\n";
        std::cout << "2. addNextAfter      8. removeNodeUpChildren\n";
        std::cout << "3. addNextBefore     9. removeNodeAdoptChildren\n";
        std::cout << "4. addSplit          p. setRoot\n";
        std::cout << "5. raiseLevel        u. setText\n";
        std::cout << "6. lowerLevel        0. Exit\n";
        std::cout << "\nMessage: " << lastMessage << "\n";
        std::cout << "Select action: ";
        
        lastMessage = "";

        int key = getKeystroke();
        TextNode* targetNode = displayList.empty() ? nullptr : displayList[selectedIndex];

        try {
            if (key == 1000 || key == 'w' || key == 'W') { 
                if (selectedIndex > 0) selectedIndex--;
            } 
            else if (key == 1001 || key == 's' || key == 'S') { 
                if (selectedIndex < displayList.size() - 1) selectedIndex++;
            } 
            else if (key == '0') {
                break;
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
            else if (key == 'u' || key == 'p'){
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
    }

    return 0;
}
