#pragma once

#include <vector>
#include <string>

class ITextNode
{
public:
   virtual ~ITextNode() = default;

   virtual void addChild(ITextNode *child) = 0;
   virtual void removeChild(size_t index) = 0;

   virtual ITextNode *getChild(size_t index) = 0;

   virtual void setTitle(const std::string &str) = 0;
   virtual const std::string getTitle() = 0;

   virtual std::string toString(size_t indent = 0) const = 0;
};