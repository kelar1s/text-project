#include "TextTreeEditor.hpp"

#include <iostream>

int main() {
    TextTreeEditor editor;

    try {
        editor.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
