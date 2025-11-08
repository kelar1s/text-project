#pragma once

#include "ITextNode.hpp"

class TextNodeBase : public ITextNode
{
protected:
   std::string title;
   std::vector<ITextNode *> children;

public:
   TextNodeBase(const std::string &str = "") : title(str) {}

   virtual ~TextNodeBase() override
   {
      for (ITextNode *child : children)
      {
         delete child;
      }
   }

   TextNodeBase(const TextNodeBase &) = delete;
   TextNodeBase &operator=(const TextNodeBase &) = delete;
   TextNodeBase(TextNodeBase &&) = delete;
   TextNodeBase &operator=(TextNodeBase &&) = delete;

   virtual void addChild(ITextNode *child) override
   {
      if (child)
      {
         children.push_back(child);
      }
   }

   virtual void removeChild(size_t index) override
   {
      if (index < children.size())
      {
         delete children[index];
         children.erase(children.begin() + index);
      }
   }

   virtual ITextNode *getChild(size_t index) override
   {
      if (index >= children.size())
      {
         throw -1;
      }
      return children[index];
   }

   virtual void setTitle(const std::string &str)
   {
      title = str;
   }

   virtual const std::string getTitle()
   {
      return title;
   }

   virtual std::string toString(size_t indent = 0) const override
   {
      std::string result(indent, ' ');
      result += "+ " + title + "\n";

      for (const ITextNode *child : children)
      {
         if (child)
         {
            result += child->toString(indent + 2);
         }
      }
      return result;
   }
};
