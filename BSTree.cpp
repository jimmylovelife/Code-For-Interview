/**
二分查找树 
**/
#include <stdio.h>
#include <stdlib.h>

typedef struct Tree{
        int data;
        struct Tree *left;
        struct Tree *right;
} BSTree;

BSTree* createBSTree() {
     BSTree *root = (BSTree *) calloc(sizeof(BSTree), sizeof(char));
     int tmp;
     scanf("%d", &tmp);
     root->data = tmp;
     root->left = NULL;
     root->right = NULL;
     
     while(scanf("%d", &tmp) != EOF) {
         BSTree *ins = root;
         while(1) {
             if(ins->data >= tmp) {
                 if(ins->left != NULL) {
                     ins = ins->left;
                     continue;
                 } else {
                     BSTree *newItem = (BSTree *) calloc(sizeof(BSTree), sizeof(char));
                     newItem->data = tmp;
                     newItem->left = NULL;
                     newItem->right = NULL;
                     ins->left = newItem;
                     break;
                 } 
             } else {
                 if(ins->right != NULL) {
                     ins = ins->right;
                     continue;
                 }  else {
                     BSTree *newItem = (BSTree *) calloc(sizeof(BSTree), sizeof(char));
                     newItem->data = tmp;
                     newItem->left = NULL;
                     newItem->right = NULL;
                     ins->right = newItem;
                     break;
                 }
             }
         }
     }
     return root;
}
//中序遍历 
void inorder(BSTree *bTree) {
     if (bTree->left != NULL) {
         inorder(bTree->left);
     }
     printf("%d\n", bTree->data);
     if(bTree->right != NULL) {
         inorder(bTree->right);
     }
     
}
//TODO add other algorithm
int main() {
    BSTree *root = createBSTree();
    inorder(root);
    system("pause");
}
