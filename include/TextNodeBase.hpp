#pragma once

#include "ITextNode.hpp"

class TextNodeBase : public ITextNode
{
protected:
   std::string title;
   std::vector<ITextNode *> children;

public:
   TextNodeBase(const std::string &str = "");

   virtual ~TextNodeBase() override;

   void addChild(ITextNode *child) override;
   void removeChild(size_t index) override;
   ITextNode *getChild(size_t index) override;
   size_t childCount() const override;

   void setTitle(const std::string &str);
   const std::string getTitle();

   std::string toString(size_t indent = 0) const override;
};
