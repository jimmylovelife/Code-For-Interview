/**
 * linus所说的不懂指针的代码示例
 */

struct Node {
	int data;
	Node *next;
};

typedef bool (* rm_func) (const Node *);

/**不聪明的做法
 * 用了prev指针
 * 但这是很多面试或笔试的标准答案
 * linus大神持反对意见
 */
Node * rm_node (Node *head, rm_func rm) {
	Node *curr = head;
	Node *prev = NULL;
	while(curr != NULL) {
		if(rm(curr)) {
			if(prev)
				prev->next = curr->next;
			else
				head = curr->next;
			free(curr);
		} else
			prev = curr;
		curr = curr->next;
	}
	return head;
}

/**
 * Linus给出的解法
 * 用二级指针
 * 巧妙解决
 */

void rm_node(Node **head, rm_func rm) {
	Node **curr = head;
	while (*curr) {
		Node *ptr = *curr;
		if(rm(*curr)) {
			*curr = ptr->next;
			free(ptr);
		} else {
			curr = &(ptr->next);
		}
	}
}
