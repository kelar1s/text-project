#include <stdexcept>
#include <string>

class TextTreeException : public std::runtime_error {
public:
    explicit TextTreeException(const std::string& message) 
        : std::runtime_error(message) {}
};

class NodeNotFoundException : public TextTreeException {
public:
    NodeNotFoundException() 
        : TextTreeException("Error: Node not found in the TextTree") {}
};

class InvalidNodeException : public TextTreeException {
public:
    explicit InvalidNodeException(const std::string& message) 
        : TextTreeException("Error: " + message) {}
};

class NodeNotSelectedException : public TextTreeException {
public:
    NodeNotSelectedException() 
        : TextTreeException("Error: Node not selected!") {}
};
