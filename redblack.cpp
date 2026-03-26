//
// Created by sophi on 3/18/2026.
//

#include <iostream>
#include <string>
using namespace std;

struct node {
  int data;
  string color;
  node *left, *right, *parent;

  node(int data) : data(data), color("RED"), left(nullptr), right(nullptr), parent(nullptr){}
};

class RedBlackTree {
  private:
    node* root;
    node* NIL;

    //rotations

    void leftRotate(node* x){
      node* y = x->right;
      x->right = y->left;

      if (y->left != NIL) {
        y->left->parent = x;
        y->parent = x->parent;
      }

      if (x->parent == nullptr){
        root = y;
      }
      else if (x == x->parent->left){
        x->parent->left = y;
      }
      else{
        x->parent->right = y;
      }

      y->left = x;
      x->parent = y;
    }

    void rightRotate(node* x){
      node* y = x->left;
      x->left = y->right;

      if (y->right != NIL) {
        y->right->parent = x;
        y->parent = x->parent;
      }

      if (x->parent == nullptr){
        root = y;
      }
      else if (x == x->parent->right){
        x->parent->right = y;
      }
      else {
        x->parent->left = y;
      }

      y->right = x;
      x->parent = y;
    }

    //checking for volor violation

    void fixInsert(node* r){
      while(r!=root&&k->parent->color=="RED"){
        if(r->parent == r->parent->parent->left){
          node*uncle = r->parent->parent->right;
          if(uncle->color == "RED"){
            r->parent->color = "BLACK";
            uncle->color = "BLACK";
            r->parent->color = "RED";
            r = r->parent->parent;
          }
          else {
            if(r==r->parent->right){
              r = r->parent;
              leftRotate(r);
            }
            r->parent->color = "BLACK";
            r->parent->parent->color = "RED";
            rightRotate(r->parent->parent);
          }
        }
        else{
          node*uncle = r->parent->parent->left;
          if(uncle->color == "RED"){
            r->parent->color = "BLACK";
            uncle->color = "BLACK";
            r->parent->parent->color = "RED";
            r = r->parent->parent;
          }
          else{
            if(r==r->parent->left){
              r = r->parent;
              rightRotate(r);
            }
            r->parent->color = "BLACK";
            r->parent->parent->color = "RED";
            leftRotate(r->parent->parent);
          }
        }
      }
      root->color = "BLACK";
    }

  public:
    RedBlackTree() : root(nullptr) {}

    // insert a node
    void insert(int val) {
        Node* newNode = new Node(val);
        Node* y = nullptr;
        Node* x = root;

        while (x != nullptr) {
            y = x;
            if (newNode->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        newNode->parent = y;
        if (y == nullptr)
            root = newNode;
        else if (newNode->data < y->data)
            y->left = newNode;
        else
            y->right = newNode;

        fixInsert(newNode);
    }
}
