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
    if(bTree == NULL)
        return;
    inorder(bTree->left);
    printf("%d,", bTree->data);
    inorder(bTree->right);
}
//先序遍历递归
void preorder(BSTree *bTree) {
    if(bTree == NULL)
        return;
    printf("%d,", bTree->data);
    preorder((bTree->left));
    preorder((bTree->right));
}

//后序遍历
void postorder(BSTree *bTree) {
    if(bTree == NULL)
        return;
    postorder(bTree->left);
    postorder(bTree->right);
    printf("%d,", bTree->data);

}

int max(int a, int b) {
    if (a >= b)
        return a;
    return b;
}

//树的最大深度
int depth_of_tree(BSTree *bTree) {
    if(bTree == NULL)
        return 0;
    return 1 + max(depth_of_tree(bTree->left), depth_of_tree(bTree->right));
}

static BSTree *array[100];
//怎样从顶部开始逐层打印二叉树结点数据
void printByLayer(BSTree *bTree) {
    int depth = depth_of_tree(bTree);
    printf("depth is %d\n", depth);
    int id = 0;
    BSTree *ptr = bTree;
    int index = 0;
    while(ptr != NULL) {
        if(ptr->left != NULL)
            array[id++] = ptr->left;
        if(ptr->right != NULL)
            array[id++] = ptr->right;
        printf("%d,", ptr->data);
        ptr = array[index++];
    }
    /*
    for(int i=1; i<=depth; i++) {

    }
    */
}

//TODO add other algorithm
int main() {
    BSTree *root = createBSTree();
    printf("中序遍历: ");
    inorder(root);
    printf("\n先序遍历： ");
    preorder(root);
    printf("\n后序遍历：");
    postorder(root);
    printf("\n逐层遍历：");
    printByLayer(root);
    //system("pause");
}
