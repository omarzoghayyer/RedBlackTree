#ifndef RBTNODE_H
#define RBTNODE_H

#include "BSTNode.h"

class RBTNode : public BSTNode {
public:
   enum Color { REDCOLOR, BLACKCOLOR };

   Color color;
    
   RBTNode(int nodeKey) : BSTNode(nodeKey) {
      color = Color::REDCOLOR;
   }
    
   // Returns true if both child nodes are black. A null child is considered to
   // be black.
   virtual bool AreBothChildrenBlack() {
      RBTNode* left = (RBTNode*) GetLeft();
      if (left && left->IsRed()) {
         return false;
      }
      RBTNode* right = (RBTNode*) GetRight();
      if (right && right->IsRed()) {
         return false;
      }
      return true;
   }
    
   virtual RBTNode* GetGrandparent() {
      if (GetParent() == nullptr) {
         return nullptr;
      }
      return (RBTNode*) GetParent()->GetParent();
   }
   
   // Returns this node's sibling, or null if this node does not have a sibling
   virtual RBTNode* GetSibling() {
      BSTNode* parent = GetParent();
      if (parent) {
         if (this == parent->GetLeft()) {
            return (RBTNode*) parent->GetRight();
         }
         return (RBTNode*) parent->GetLeft();
      }
      return nullptr;
   }
   
   // Returns the uncle of this node
   virtual RBTNode* GetUncle() {
      RBTNode* grandparent = GetGrandparent();
      if (grandparent == nullptr) {
         return nullptr;
      }
      if (grandparent->GetLeft() == GetParent()) {
         return (RBTNode*) grandparent->GetRight();
      }
      return (RBTNode*) grandparent->GetLeft();
   }
   
   // Returns true if this node is black, false otherwise
   virtual bool IsBlack() {
      return color == Color::BLACKCOLOR;
   }
   
   // Returns true if this node's left child is non-null and red. Returns false
   // otherwise.
   virtual bool IsLeftChildRed() {
      RBTNode* leftChild = (RBTNode*) GetLeft();
      if (leftChild) {
         return leftChild->color == Color::REDCOLOR;
      }
      return false;
   }
   
   virtual bool IsParentNull() {
      return GetParent() == nullptr;
   }
   
   // Returns true if this node's right child is non-null and red. Returns
   // false otherwise.
   virtual bool IsRightChildRed() {
      RBTNode* rightChild = (RBTNode*) GetRight();
      if (rightChild) {
         return rightChild->color == Color::REDCOLOR;
      }
      return false;
   }
   
   // Returns true if this node is red, false otherwise
   virtual bool IsRed() {
      return color == Color::REDCOLOR;
   }
   
   virtual std::string ToString() {
      using namespace std;
      return to_string(GetKey()) + (IsRed() ? " R" : " B");
   }
};

#endif