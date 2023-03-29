#ifndef EXTENDEDREDBLACKTREE_H
#define EXTENDEDREDBLACKTREE_H

#include "RedBlackTree.h"
#include "ExtendedRBTNode.h"

class ExtendedRedBlackTree : public RedBlackTree {
protected:
   // Each node in an ExtendedRedBlackTree is an ExtendedRBTNode
   virtual BSTNode* MakeNewNode(int key) override {
      return new ExtendedRBTNode(key);
   }

   // Your code here

public:
   virtual int GetNthKey(int n) override {
      // Your code here (remove placeholder line below)
      return 0;
   }
};

#endif