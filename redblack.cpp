// //
// // Created by sophi on 3/18/2026.
// //

#include <iostream>
#include <string>
using namespace std;

// struct rbnode {
//   int data;
//   string color;
//   rbnode *left, *right, *parent;

//   rbnode(int data) : data(data), color("RED"), left(nullptr), right(nullptr), parent(nullptr){}
// };

// class RedBlackTree {
//   private:
//     rbnode* root;
//     rbnode* NIL;

//     //rotations

//     void leftRotate(rbnode* x){
//       rbnode* y = x->right;
//       x->right = y->left;

//       if (y->left != NIL) {
//         y->left->parent = x;
//         y->parent = x->parent;
//       }

//       if (x->parent == nullptr){
//         root = y;
//       }
//       else if (x == x->parent->left){
//         x->parent->left = y;
//       }
//       else{
//         x->parent->right = y;
//       }

//       y->left = x;
//       x->parent = y;
//     }

//     void rightRotate(rbnode* x){
//       rbnode* y = x->left;
//       x->left = y->right;

//       if (y->right != NIL) {
//         y->right->parent = x;
//         y->parent = x->parent;
//       }

//       if (x->parent == nullptr){
//         root = y;
//       }
//       else if (x == x->parent->right){
//         x->parent->right = y;
//       }
//       else {
//         x->parent->left = y;
//       }

//       y->right = x;
//       x->parent = y;
//     }

//     //checking for color violation

//     void fixInsert(rbnode* r){
//       while(r!=root&&r->parent->color=="RED"){
//         if(r->parent == r->parent->parent->left){
//           rbnode*uncle = r->parent->parent->right;
//           if(uncle->color == "RED"){
//             r->parent->color = "BLACK";
//             uncle->color = "BLACK";
//             r->parent->color = "RED";
//             r = r->parent->parent;
//           }
//           else {
//             if(r==r->parent->right){
//               r = r->parent;
//               leftRotate(r);
//             }
//             r->parent->color = "BLACK";
//             r->parent->parent->color = "RED";
//             rightRotate(r->parent->parent);
//           }
//         }
//         else{
//           rbnode*uncle = r->parent->parent->left;
//           if(uncle->color == "RED"){
//             r->parent->color = "BLACK";
//             uncle->color = "BLACK";
//             r->parent->parent->color = "RED";
//             r = r->parent->parent;
//           }
//           else{
//             if(r==r->parent->left){
//               r = r->parent;
//               rightRotate(r);
//             }
//             r->parent->color = "BLACK";
//             r->parent->parent->color = "RED";
//             leftRotate(r->parent->parent);
//           }
//         }
//       }
//       root->color = "BLACK";
//     }

//   public:
//     RedBlackTree() : root(nullptr) {}

//     // insert a rbnode
//     void insert(int val) {
//         rbnode* newrbnode = new rbnode(val);
//         rbnode* y = nullptr;
//         rbnode* x = root;

//         while (x != nullptr) {
//             y = x;
//             if (newrbnode->data < x->data)
//                 x = x->left;
//             else
//                 x = x->right;
//         }

//         newrbnode->parent = y;
//         if (y == nullptr)
//             root = newrbnode;
//         else if (newrbnode->data < y->data)
//             y->left = newrbnode;
//         else
//             y->right = newrbnode;

//         fixInsert(newrbnode);
//     }
// };

#include "MenuItem.h"

struct rbnode {
    MenuItem data;
    string color;
    rbnode *left, *right, *parent;

    rbnode(const MenuItem& data)
        : data(data), color("RED"), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    rbnode* root;

    // rotations
    void leftRotate(rbnode* x){
        rbnode* y = x->right;
        x->right = y->left;

        if (y->left != nullptr)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rightRotate(rbnode* x){
        rbnode* y = x->left;
        x->left = y->right;

        if (y->right != nullptr)
            y->right->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;

        y->right = x;
        x->parent = y;
    }

    void fixInsert(rbnode* r){
        while (r != root && r->parent->color == "RED"){
            if (r->parent == r->parent->parent->left){
                rbnode* uncle = r->parent->parent->right;

                if (uncle && uncle->color == "RED"){
                    r->parent->color = "BLACK";
                    uncle->color = "BLACK";
                    r->parent->parent->color = "RED";
                    r = r->parent->parent;
                } else {
                    if (r == r->parent->right){
                        r = r->parent;
                        leftRotate(r);
                    }
                    r->parent->color = "BLACK";
                    r->parent->parent->color = "RED";
                    rightRotate(r->parent->parent);
                }
            } else {
                rbnode* uncle = r->parent->parent->left;

                if (uncle && uncle->color == "RED"){
                    r->parent->color = "BLACK";
                    uncle->color = "BLACK";
                    r->parent->parent->color = "RED";
                    r = r->parent->parent;
                } else {
                    if (r == r->parent->left){
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

    void insert(const MenuItem& item){
        rbnode* newNode = new rbnode(item);
        rbnode* y = nullptr;
        rbnode* x = root;

        while (x != nullptr){
            y = x;
            if (item.getRestaurant() < x->data.getRestaurant())
                x = x->left;
            else
                x = x->right;
        }

        newNode->parent = y;

        if (y == nullptr)
            root = newNode;
        else if (item.getRestaurant() < y->data.getRestaurant())
            y->left = newNode;
        else
            y->right = newNode;

        fixInsert(newNode);
    }
};