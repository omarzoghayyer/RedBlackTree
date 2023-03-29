#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <algorithm>
#include "BinarySearchTree.h"
#include "RBTNode.h"

class RedBlackTree : public BinarySearchTree {
private:
   void PrepareForRemoval(RBTNode* node) {
      if (TryCase1(node)) {
         return;
      }

      RBTNode* sibling = node->GetSibling();
      if (TryCase2(node, sibling)) {
         sibling = node->GetSibling();
      }
      if (TryCase3(node, sibling)) {
         return;
      }
      if (TryCase4(node, sibling)) {
         return;
      }
      if (TryCase5(node, sibling)) {
         sibling = node->GetSibling();
      }
      if (TryCase6(node, sibling)) {
         sibling = node->GetSibling();
      }

      RBTNode* nodeParent = (RBTNode*) node->GetParent();
      sibling->color = nodeParent->color;
      nodeParent->color = RBTNode::BLACKCOLOR;
      if (node == nodeParent->GetLeft()) {
         ((RBTNode*)sibling->GetRight())->color = RBTNode::BLACKCOLOR;
         RotateLeft(nodeParent);
      }
      else {
         ((RBTNode*)sibling->GetLeft())->color = RBTNode::BLACKCOLOR;
         RotateRight(nodeParent);
      }
   }
   
   bool TryCase1(RBTNode* node) {
      if (node->IsRed() || node->IsParentNull()) {
         return true;
      }
      return false; // not case 1
   }
   
   bool TryCase2(RBTNode* node, RBTNode* sibling) {
      if (sibling->IsRed()) {
         RBTNode* nodeParent = (RBTNode*) node->GetParent();
         nodeParent->color = RBTNode::REDCOLOR;
         sibling->color = RBTNode::BLACKCOLOR;
         if (node == nodeParent->GetLeft()) {
            RotateLeft(nodeParent);
         }
         else {
            RotateRight(nodeParent);
         }
         return true;
      }
      return false; // not case 2
   }
   
   bool TryCase3(RBTNode* node, RBTNode* sibling) {
      RBTNode* nodeParent = (RBTNode*) node->GetParent();
      if (nodeParent->IsBlack() && sibling->AreBothChildrenBlack()) {
         sibling->color = RBTNode::REDCOLOR;
         PrepareForRemoval(nodeParent);
         return true;
      }
      return false; // not case 3
   }
   
   bool TryCase4(RBTNode* node, RBTNode* sibling) {
      RBTNode* nodeParent = (RBTNode*) node->GetParent();
      if (nodeParent->IsRed() && sibling->AreBothChildrenBlack()) {
         nodeParent->color = RBTNode::BLACKCOLOR;
         sibling->color = RBTNode::REDCOLOR;
         return true;
      }
      return false; // not case 4
   }
   
   bool TryCase5(RBTNode* node, RBTNode* sibling) {
      if (sibling->IsLeftChildRed()) {
         if (!sibling->IsRightChildRed()) {
            if (node == node->GetParent()->GetLeft()) {
               sibling->color = RBTNode::REDCOLOR;
               ((RBTNode*)sibling->GetLeft())->color = RBTNode::BLACKCOLOR;
               RotateRight(sibling);
               return true;
            }
         }
      }
      return false; // not case 5
   }
   
   bool TryCase6(RBTNode* node, RBTNode* sibling) {
      if (!sibling->IsLeftChildRed()) {
         if (sibling->IsRightChildRed()) {
            if (node == node->GetParent()->GetRight()) {
               sibling->color = RBTNode::REDCOLOR;
               ((RBTNode*)sibling->GetRight())->color = RBTNode::BLACKCOLOR;
               RotateLeft(sibling);
               return true;
            }
         }
      }
      return false; // not case 6
   }

protected:
   virtual void InsertNode(BSTNode* node) override {
      // Red-black tree insertion starts with the standard BST insertion
      BinarySearchTree::InsertNode(node);

      // Color the node red, then balance
      ((RBTNode*)node)->color = RBTNode::REDCOLOR;
      InsertionBalance((RBTNode*)node);
   }

   virtual BSTNode* MakeNewNode(int key) override {
      return new RBTNode(key);
   }
   
   virtual bool RemoveNode(BSTNode* bstNode) override {
      if (!bstNode) {
         return false;
      }
      
      RBTNode* node = (RBTNode*) bstNode;
      if (node->GetLeft() && node->GetRight()) {
         // Get the node's predecessor
         RBTNode* predecessorNode = (RBTNode*) node->GetLeft();
         while (predecessorNode->GetRight()) {
            predecessorNode = (RBTNode*) predecessorNode->GetRight();
         }
         
         // Get predecessor's key, then recursively remove the predecessor node
         int predecessorKey = predecessorNode->GetKey();
         RemoveNode(predecessorNode);
         
         // Assign the node's key with the now-removed predecessor node's key
         node->SetKey(predecessorKey);
         
         return true;
      }

      if (node->IsBlack()) {
         PrepareForRemoval(node);
      }
      BinarySearchTree::RemoveNode(node);

      // One special case if the root was changed to red
      RBTNode* rootNode = (RBTNode*) GetRoot();
      if (rootNode && rootNode->IsRed()) {
         rootNode->color = RBTNode::BLACKCOLOR;
      }
      
      return true;
   }

public:
   RedBlackTree() {
      // Note: Parent class's constructor does all needed work
   }
   
   void InsertionBalance(RBTNode* node) {
      // If node is the tree's root, then color node black and return
      if (node->IsParentNull()) {
         node->color = RBTNode::BLACKCOLOR;
         return;
      }
      
      // Pointer to parent node is needed for remaining operations
      RBTNode* parent = (RBTNode*) node->GetParent();
        
      // If parent is black, then return without any changes
      if (parent->IsBlack()) {
         return;
      }
    
      // Pointers tograndparent and uncle are needed for remaining operations
      RBTNode* grandparent = node->GetGrandparent();
      RBTNode* uncle = node->GetUncle();
        
      // If parent and uncle are both red, then color parent and uncle black, 
      // color grandparent red, recursively balance  grandparent, then return
      if (uncle && uncle->IsRed()) {
         parent->color = uncle->color = RBTNode::BLACKCOLOR;
         grandparent->color = RBTNode::REDCOLOR;
         InsertionBalance(grandparent);
         return;
      }

      // If node is parent's right child and parent is grandparent's left
      // child, then rotate left at parent, update node and parent to point to
      // parent and grandparent, respectively
      if (node == parent->GetRight() && parent == grandparent->GetLeft()) {
         RotateLeft(parent);
         node = parent;
         parent = (RBTNode*) node->GetParent();
      }
      // Else if node is parent's left child and parent is grandparent's right 
      // child, then rotate right at parent, update node and parent to point to 
      // parent and grandparent, respectively
      else if (node == parent->GetLeft() && parent == grandparent->GetRight()) {
         RotateRight(parent);
         node = parent;
         parent = (RBTNode*) node->GetParent();
      }

      // Color parent black and grandparent red
      parent->color = RBTNode::BLACKCOLOR;
      grandparent->color = RBTNode::REDCOLOR;
                
      // If node is parent's left child, then rotate right at grandparent, 
      // otherwise rotate left at grandparent
      if (node == parent->GetLeft()) {
         RotateRight(grandparent);
      }
      else {
         RotateLeft(grandparent);
      }
   }
   
   bool IsNullOrBlack(RBTNode* node) {
      if (node == nullptr) {
         return true;
      }
      return node->IsBlack();
   }
   
   bool IsNotNullAndRed(RBTNode* node) {
      if (node == nullptr) {
         return false;
      }
      return node->IsRed();
   }
};

#endif