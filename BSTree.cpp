/**
���ֲ�����
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
//�������
void inorder(BSTree *bTree) {
    if(bTree == NULL)
        return;
    inorder(bTree->left);
    printf("%d,", bTree->data);
    inorder(bTree->right);
}
//��������ݹ�
void preorder(BSTree *bTree) {
    if(bTree == NULL)
        return;
    printf("%d,", bTree->data);
    preorder((bTree->left));
    preorder((bTree->right));
}

//�������
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

//����������
int depth_of_tree(BSTree *bTree) {
    if(bTree == NULL)
        return 0;
    return 1 + max(depth_of_tree(bTree->left), depth_of_tree(bTree->right));
}

static BSTree *array[100];
static int depth;
void display(BSTree *item, int layer, bool flag) {
	//printf("print item->data:%d\n", item->data->data);
	for (int i=0; i<depth-layer; i++)
		printf(" ");
	if (item == NULL)
		printf(" ");
	else 
		printf("%d", item->data);
	if(flag)
		printf(" ");
}
//�����Ӷ�����ʼ����ӡ�������������
void printByLayer(BSTree *bTree) {
    depth = depth_of_tree(bTree);
    printf("depth is %d\n", depth);
    BSTree *ptr = bTree;
	array[0] = ptr;
	int id = 0, last=0;
    for(int i=1; i<=depth; i++) {
		int k = pow(2, i-1);
		bool left = true;//��ӡ���
		while(k>0) {
			display(array[id], i, left);
			if(array[id] == NULL) {
				array[++last] = NULL;
				array[++last] = NULL;
			} else {
				//printf("Enqueue %d,%d\n", item->data->left->data, item->data->right->data);
				array[++last] = array[id]->left;
				array[++last] = array[id]->right;
			}
			k--;
			id++;
			left = !left;
    	}
		printf("\n");
	}
}
//�Ƿ���ƽ�������
bool isBalanceTree(BSTree *bTree) {
	if(bTree == NULL) 
		return true;
	return (abs(depth_of_tree(bTree->left) - depth_of_tree(bTree->right)) <= 1);
}

int numOfChild(BSTree *tTree, BSTree* ch1, BSTree *ch2) {
	if (tTree == NULL)
		return 0;
	if(tTree == ch1 || tTree == ch2)
		return 1;
	int left = 0, right = 0;
	left = numOfChild(tTree->left, ch1, ch2);
	right = numOfChild(tTree->right, ch1, ch2);
	return left + right;
}

//�����������������ڵ�������ͬ�����
BSTree *commonFather(BSTree *tTree, BSTree* ch1, BSTree* ch2) {
	int left = 0, right = 0;
	left = numOfChild(tTree->left, ch1, ch2);
	right = numOfChild(tTree->right, ch1, ch2);

	if (left == 2) return commonFather(tTree->left, ch1, ch2);
	if (right == 2) return commonFather(tTree->right, ch1, ch2);
	if (left == 1 && right == 1) return tTree;
	return NULL;
}	
//TODO add other algorithm
int main() {
    BSTree *root = createBSTree();
    printf("�������: ");
    inorder(root);
    printf("\n��������� ");
    preorder(root);
    printf("\n���������");
    postorder(root);
    printf("\n��������");
    printByLayer(root);
	if(isBalanceTree(root))
		printf("is balance tree\n");
	else 
		printf("not a balance tree\n");
}
