/**
 * min stack
 * push, pop, min ¶¼ÊÇo(1)
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INIT_LEN 1024
#define FACTOR 2
#define IS_FULL(s) (s->len == s->cap)
#define IS_EMPTY(s) (s->len == 0)

struct MStack {
	int *data;
	size_t cap;
	size_t len;
};

struct MinStack {
	MStack *minStack;
	MStack *dataStack;
};

static int top(MStack *s) {
	return s->data[s->len-1];
}

static int pop(MStack *s) {
	return s->data[--(s->len)];
}

static size_t min(MinStack *s) {
	return top(s->minStack);
}

static void push (MStack *s, int data) {
	if (IS_FULL(s)) {
		//À©Õ¹´æ´¢
	}
	s->data[(s->len)++] = data;
}
static void push(MinStack *s, int data) {
	if(IS_EMPTY(s->dataStack))
		push(s->minStack, 0);
	else {
		size_t minIndex = min(s);
		int minValue = s->dataStack->data[minIndex];
		push(s->minStack, ((minValue <= data) ? minIndex : s->dataStack->len ));	
	}
	push(s->dataStack, data);
}

static void init_stack(MStack *s) {
	if (s == NULL) {
		perror("stack should not be null\n");
		exit(1);
	}
	s->data = (int *)malloc(INIT_LEN);
	s->cap = INIT_LEN;
	s->len = 0;
}

int main() {
	MinStack *stack = (MinStack *)malloc(sizeof(MinStack));
	stack->dataStack = (MStack *)malloc(sizeof(MStack));
	stack->minStack = (MStack *) malloc(sizeof(MStack));
	init_stack(stack->dataStack);
	init_stack(stack->minStack);
	int array[] = {1,3,9,-1,-3,2,4,-4,3};
	for (int i=0; i<9; i++) {
		push(stack, array[i]);
		printf("%d,", min(stack));
	}
}
