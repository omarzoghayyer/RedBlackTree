#ifndef EXTENDEDRBTNODE_H
#define EXTENDEDRBTNODE_H

#include "RBTNode.h"

class ExtendedRBTNode : public RBTNode {
private:
   int subtreeKeyCount;

public:
   ExtendedRBTNode(int nodeKey) : RBTNode(nodeKey) {
      subtreeKeyCount = 1;
   }
   
   virtual int GetSubtreeKeyCount() override {
      return subtreeKeyCount;
   }
   
   // Your code here
};

#endif