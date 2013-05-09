/**
 * linus��˵�Ĳ���ָ��Ĵ���ʾ��
 */

struct Node {
	int data;
	Node *next;
};

typedef bool (* rm_func) (const Node *);

/**������������
 * ����prevָ��
 * �����Ǻܶ����Ի���Եı�׼��
 * linus����ַ������
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
 * Linus�����Ľⷨ
 * �ö���ָ��
 * ������
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
